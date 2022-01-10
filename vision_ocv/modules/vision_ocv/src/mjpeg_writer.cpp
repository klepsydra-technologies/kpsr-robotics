#include <klepsydra/vision_ocv/mpeg_writer.h>

#include <sys/socket.h>
#include <sys/signal.h>
#include <arpa/inet.h>

#include <spdlog/spdlog.h>

#include <opencv2/opencv.hpp>

#define SOCKADDR    struct sockaddr
#define SOCKADDR_IN  struct sockaddr_in
#define INVALID_SOCKET -1
#define SOCKET_ERROR   -1
#define NUM_CONNECTIONS 10


kpsr::vision_ocv::SocketClient::SocketClient(SOCKET client, kpsr::Subscriber<std::vector<uchar>> * encodedImageSubscriber)
    : _isValid(true)
    , _client(client)
    , _encodedImageSubscriber(encodedImageSubscriber)
{
    spdlog::info("kpsr::vision_ocv::SocketClient::SocketClient. _client: {}", _client);
    // send http header
    std::string header;
    header += "HTTP/1.0 200 OK\r\n";
    header += "Cache-Control: no-cache\r\n";
    header += "Pragma: no-cache\r\n";
    header += "Connection: close\r\n";
    header += "Content-Type: multipart/x-mixed-replace; boundary=mjpegstream\r\n\r\n";
    const int headerSize = header.size();
    spdlog::info("kpsr::vision_ocv::SocketClient::SocketClient: header: {}", header);
    char* headerData = (char*)header.data();
    int writtenBytes = write(headerData, headerSize);
    spdlog::info("kpsr::vision_ocv::SocketClient::SocketClient. writtenBytes: {}", writtenBytes);
    if (writtenBytes <= 0) {
        _isValid = false;
        return;
    }

    _encodedImageSubscriber->registerListener(std::to_string(_client), std::bind(&SocketClient::onImageReceived, this, std::placeholders::_1));
}

kpsr::vision_ocv::SocketClient::~SocketClient() {
    _encodedImageSubscriber->removeListener(std::to_string(_client));
}

void kpsr::vision_ocv::SocketClient::onImageReceived(const std::vector<uchar> & encodedImage) {
    spdlog::info("kpsr::vision_ocv::SocketClient::onImageReceived. _isValid: {}", _isValid);
    if (_isValid) {
        std::stringstream head;
        head << "--mjpegstream\r\nContent-Type: image/jpeg\r\nContent-Length: " << encodedImage.size() << "\r\n\r\n";
        std::string stringHead = head.str();
        int writtenBytes = write((char*) stringHead.c_str(), stringHead.size());
        spdlog::info("kpsr::vision_ocv::SocketClient::onImageReceived. writtenBytes: {} to _client: {}", writtenBytes, _client);
        if (writtenBytes < static_cast<int>(stringHead.size())) {
            ::shutdown(_client, 2);
            _isValid = false;
        }
        writtenBytes = write((char*)(encodedImage.data()), encodedImage.size());
        spdlog::info("kpsr::vision_ocv::SocketClient::onImageReceived. writtenBytes: {} to _client: {}", writtenBytes, _client);
        if (writtenBytes < static_cast<int>(encodedImage.size())) {
            ::shutdown(_client, 2);
            _isValid = false;
        }
    }
}

bool kpsr::vision_ocv::SocketClient::isValid() {
    return _isValid;
}

int kpsr::vision_ocv::SocketClient::write(char *s, int len)
{
    if (len < 1) {
        len = strlen(s);
    }
    try {
        int retval = ::send(_client, s, len, 0x4000);
        return retval;
    }
    catch (int e) {
        spdlog::error("An exception occurred. Exception: {}", e);
    }
    return -1;
}

int kpsr::vision_ocv::MJPEGWriter::read(int socket, char* buffer)
{
    int result;
    result = recv(socket, buffer, 4096, MSG_PEEK);
    if (result < 0 )
    {
        spdlog::error("An error occurred. Error Nr: {}", result);
        return result;
    }
    std::string s = buffer;
    buffer = (char*) s.substr(0, (int) result).c_str();
    return result;
}

kpsr::vision_ocv::MJPEGWriter::MJPEGWriter(int port,
                                           int timeout,
                                           int quality,
                                           kpsr::Subscriber<kpsr::vision_ocv::ImageData> * imageSubscriber,
                                           kpsr::Publisher<std::vector<uchar>> * encodedImagePublisher,
                                           kpsr::Subscriber<std::vector<uchar>> * encodedImageSubscriber)
    : _socket(INVALID_SOCKET)
    , timeout(timeout)
    , quality(quality)
    , port(port)
    , _imageSubscriber(imageSubscriber)
    , _encodedImagePublisher(encodedImagePublisher)
    , _encodedImageSubscriber(encodedImageSubscriber)
    , _isValid(false)
    , _isRunning(false)
{
    signal(SIGPIPE, SIG_IGN);
    FD_ZERO(&master);
    _imageSubscriber->registerListener("MJPEGWriter", std::bind(&MJPEGWriter::onImageReceived, this, std::placeholders::_1));

}

kpsr::vision_ocv::MJPEGWriter::~MJPEGWriter()
{
    release();
    _imageSubscriber->removeListener("MJPEGWriter");
}

bool kpsr::vision_ocv::MJPEGWriter::release()
{
    if (_socket != INVALID_SOCKET)
        shutdown(_socket, 2);
    _socket = (INVALID_SOCKET);
    return false;
}

bool kpsr::vision_ocv::MJPEGWriter::open()
{
    _socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN address;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    if (::bind(_socket, (SOCKADDR*)&address, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
    {
        spdlog::error("couldn't bind _socket {} to port {}.", _socket, port);
        return release();
    }
    if (listen(_socket, NUM_CONNECTIONS) == SOCKET_ERROR)
    {
        spdlog::error("couldn't listen on _socket {} on port {}.", _socket, port);
        return release();
    }
    FD_SET(_socket, &master);
    return true;
}

void kpsr::vision_ocv::MJPEGWriter::onImageReceived(const kpsr::vision_ocv::ImageData & frame){
    spdlog::info("kpsr::vision_ocv::MJPEGWriter::onImageReceived. frame.seq {}.", frame.seq);
    std::vector<uchar> outbuf;
    std::vector<int> params;
    params.push_back(cv::IMWRITE_JPEG_QUALITY);
    params.push_back(quality);
    imencode(".jpg", frame.img, outbuf, params);

    _encodedImagePublisher->publish(outbuf);
}

void kpsr::vision_ocv::MJPEGWriter::start()
{
    _isRunning = true;
    _server = std::thread([this]() {
        bool isOpened = this->open();
        if (!isOpened) {
            return;
        }

        fd_set rread;
        SOCKET maxfd;

        while (_isRunning)
        {
            rread = master;
            struct timeval to = { 1, 0 };
            maxfd = _socket + 1;
            spdlog::debug("kpsr::vision_ocv::MJPEGWriter. started");
            int sel = select(maxfd, &rread, NULL, NULL, &to);
            spdlog::debug("kpsr::vision_ocv::MJPEGWriter. sel: {}", sel);
            if (sel > 0) {
                for (int s = 0; s < maxfd; s++)
                {
                    if (FD_ISSET(s, &rread) && s == _socket)
                    {
                        spdlog::debug("kpsr::vision_ocv::MJPEGWriter. FD_ISSET");
                        int         addrlen = sizeof(SOCKADDR);
                        SOCKADDR_IN address = { 0 };
                        SOCKET      client = accept(_socket, (SOCKADDR*)&address, (socklen_t*)&addrlen);
                        if (client == SOCKET_ERROR)
                        {
                            spdlog::error("error : couldn't accept connection on _socket {}.", _socket);
                            return;
                        }
                        maxfd = (maxfd>client ? maxfd : client);
                        char headers[4096] = "\0";
                        spdlog::info("kpsr::vision_ocv::MJPEGWriter. Before read");
                        int readBytes = read(client, headers);
                        spdlog::info("kpsr::vision_ocv::MJPEGWriter. new client {} sent {} chars", client, readBytes);
                        clients.push_back(std::make_shared<SocketClient>(client, _encodedImageSubscriber));
                        clients.erase(
                                    std::remove_if(
                                        clients.begin(), clients.end(),
                                        [](std::shared_ptr<SocketClient> socketClient){ return !socketClient->isValid();}),
                                clients.end());
                    }
                }
            }
            usleep(100000);
        }
    });
}

void kpsr::vision_ocv::MJPEGWriter::stop()
{
    _isRunning = false;
    _server.join();
}
