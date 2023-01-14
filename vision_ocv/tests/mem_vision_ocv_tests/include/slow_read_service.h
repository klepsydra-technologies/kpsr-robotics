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

#ifndef SLOW_READ_SERVICE_H
#define SLOW_READ_SERVICE_H

#include <thread>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"

#include <klepsydra/core/service.h>
#include <klepsydra/core/subscriber.h>

#include <klepsydra/vision_ocv/image_event_data.h>

class SlowReadService : public kpsr::Service
{
public:
    SlowReadService(kpsr::Environment *environment,
                    kpsr::Subscriber<kpsr::vision_ocv::ImageData> *subscriber)
        : kpsr::Service(environment, "SlowReadService")
        , _subscriber(subscriber)
    {}

    void start()
    {
        std::function<void(kpsr::vision_ocv::ImageData)> simpleListener =
            std::bind(&SlowReadService::onEventReceived, this, std::placeholders::_1);
        this->_subscriber->registerListener("SlowReadService", simpleListener);
    }

    void stop() { this->_subscriber->removeListener("SlowReadService"); }

    void execute() {}

    void onEventReceived(const kpsr::vision_ocv::ImageData &event)
    {
        spdlog::info("SlowReadService. event received. {}"
                     ". image type: {}"
                     ". image rows: {}"
                     ". image cols: {}",
                     event.seq,
                     event.img.type(),
                     event.img.rows,
                     event.img.cols);
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
        lastReadImg = event;
        receivedImage = true;
        receivedEvents++;
    }

    bool receivedImage = false;
    kpsr::vision_ocv::ImageData lastReadImg;
    int receivedEvents = 0;

private:
    kpsr::Subscriber<kpsr::vision_ocv::ImageData> *_subscriber;
    long _startTimestamp;
};

#endif // SLOW_READ_SERVICE_H
