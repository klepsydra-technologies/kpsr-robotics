/*
 * Copyright 2023 Klepsydra Technologies AG
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MPEG_WRITER_H
#define MPEG_WRITER_H

#define SOCKET int

#include <klepsydra/core/publisher.h>
#include <klepsydra/core/subscriber.h>
#include <klepsydra/vision_ocv/image_event_data.h>

namespace kpsr {
namespace vision_ocv {

class SocketClient
{
public:
    SocketClient(SOCKET client, kpsr::Subscriber<std::vector<uchar>> *encodedImageSubscriber);
    ~SocketClient();

    void onImageReceived(const std::vector<uchar> &encodedImage);

    bool isValid();

private:
    int write(char *s, int len);

    bool _isValid;
    SOCKET _client;
    kpsr::Subscriber<std::vector<uchar>> *_encodedImageSubscriber;
};

class MJPEGWriter
{
public:
    MJPEGWriter(int port,
                int timeout,
                int quality,
                kpsr::Subscriber<kpsr::vision_ocv::ImageData> *imageSubscriber,
                kpsr::Publisher<std::vector<uchar>> *encodedImagePublisher,
                kpsr::Subscriber<std::vector<uchar>> *encodedImageSubscriber);

    ~MJPEGWriter();

    void start();
    void stop();

private:
    void onImageReceived(const kpsr::vision_ocv::ImageData &frame);
    bool release();
    bool open();
    int read(int socket, char *buffer);

    SOCKET _socket;
    int timeout;
    int quality;
    int port;

    kpsr::Subscriber<kpsr::vision_ocv::ImageData> *_imageSubscriber;
    kpsr::Publisher<std::vector<uchar>> *_encodedImagePublisher;
    kpsr::Subscriber<std::vector<uchar>> *_encodedImageSubscriber;

    fd_set master;
    std::vector<std::shared_ptr<SocketClient>> clients;
    std::thread _server;
    bool _isValid;
    std::atomic_bool _isRunning;
};
} // namespace vision_ocv
} // namespace kpsr

#endif //MPEG_WRITER_H
