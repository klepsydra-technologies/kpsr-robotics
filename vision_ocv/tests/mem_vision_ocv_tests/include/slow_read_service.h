/****************************************************************************
*
*                           Klepsydra Core Modules
*              Copyright (C) 2019-2020  Klepsydra Technologies GmbH
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

#ifndef SLOW_READ_SERVICE_H
#define SLOW_READ_SERVICE_H

#include <thread>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

#include <klepsydra/core/service.h>
#include <klepsydra/core/subscriber.h>

#include <klepsydra/vision_ocv/image_event_data.h>

class SlowReadService : public kpsr::Service
{
public:
    SlowReadService(kpsr::Environment * environment, kpsr::Subscriber<kpsr::vision_ocv::ImageData> * subscriber)
        : kpsr::Service(environment, "SlowReadService")
        , _subscriber(subscriber)
    {}

    void start() {
        std::function<void(kpsr::vision_ocv::ImageData)> simpleListener = std::bind(&SlowReadService::onEventReceived, this, std::placeholders::_1);
        this->_subscriber->registerListener("SlowReadService", simpleListener);
    }

    void stop() {
        this->_subscriber->removeListener("SlowReadService");
    }

    void execute() {}

    void onEventReceived(const kpsr::vision_ocv::ImageData & event) {
        spdlog::info("SlowReadService. event received. {}"
                  ". image type: {}"
                  ". image rows: {}"
                  ". image cols: {}",
                  event.seq,
                  event.img.type(),
                  event.img.rows,
                  event.img.cols
        );
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
        lastReadImg = event;
        receivedImage = true;
        receivedEvents++;
    }

    bool receivedImage = false;
    kpsr::vision_ocv::ImageData lastReadImg;
    int receivedEvents = 0;

private:
    kpsr::Subscriber<kpsr::vision_ocv::ImageData> * _subscriber;
    long _startTimestamp;
};


#endif // SLOW_READ_SERVICE_H
