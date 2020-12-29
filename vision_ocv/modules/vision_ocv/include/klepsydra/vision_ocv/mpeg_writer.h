/****************************************************************************
*
*                           Klepsydra Core Modules
*              Copyright (C) 2020-2022  Klepsydra Technologies GmbH
*                            All Rights Reserved.
*
*  This file is subject to the terms and conditions defined in
*  file 'LICENSE.md', which is part of this source code package.
*
*  NOTICE:  All information contained herein is, and remains the property of Klepsydra
*  Technologies GmbH and its suppliers, if any. The intellectual and technical concepts
*  contained herein are proprietary to Klepsydra Technologies GmbH and its suppliers and
*  may be covered by Swiss and Foreign Patents, patents in process, and are protected by
*  trade secret or copyright law. Dissemination of this information or reproduction of
*  this material is strictly forbidden unless prior written permission is obtained from
*  Klepsydra Technologies GmbH.
*
*****************************************************************************/

#ifndef MPEG_WRITER_H
#define MPEG_WRITER_H

#define SOCKET    int

#include <klepsydra/vision_ocv/image_event_data.h>
#include <klepsydra/core/subscriber.h>
#include <klepsydra/core/publisher.h>

namespace kpsr {
namespace vision_ocv {

class SocketClient {
public:
    SocketClient(SOCKET client, kpsr::Subscriber<std::vector<uchar>> * encodedImageSubscriber);
    ~SocketClient();

    void onImageReceived(const std::vector<uchar> & encodedImage);

    bool isValid();

private:
    int write(char *s, int len);

    bool _isValid;
    SOCKET _client;
    kpsr::Subscriber<std::vector<uchar>> * _encodedImageSubscriber;
};

class MJPEGWriter{
public:

    MJPEGWriter(int port,
                int timeout,
                int quality,
                kpsr::Subscriber<kpsr::vision_ocv::ImageData> * imageSubscriber,
                kpsr::Publisher<std::vector<uchar>> * encodedImagePublisher,
                kpsr::Subscriber<std::vector<uchar>> * encodedImageSubscriber);

    ~MJPEGWriter();

    void start();
    void stop();

private:
    void onImageReceived(const kpsr::vision_ocv::ImageData & frame);
    bool release();
    bool open();
    int read(int socket, char* buffer);

    SOCKET _socket;
    int timeout;
    int quality;
    int port;

    kpsr::Subscriber<kpsr::vision_ocv::ImageData> * _imageSubscriber;
    kpsr::Publisher<std::vector<uchar>> * _encodedImagePublisher;
    kpsr::Subscriber<std::vector<uchar>> * _encodedImageSubscriber;

    fd_set master;
    std::vector<std::shared_ptr<SocketClient>> clients;
    std::thread _server;
    bool _isValid;
    std::atomic_bool _isRunning;
};
}
}

#endif //MPEG_WRITER_H
