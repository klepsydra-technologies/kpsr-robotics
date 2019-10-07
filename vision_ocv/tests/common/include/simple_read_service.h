/****************************************************************************
*
*                           Klepsydra Core Modules
*              Copyright (C) 2019-2020  Klepsydra Technologies GmbH
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*****************************************************************************/

#ifndef SIMPLE_READ_SERVICE_H
#define SIMPLE_READ_SERVICE_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

#include <klepsydra/core/service.h>
#include <klepsydra/core/subscriber.h>

#include <klepsydra/vision_ocv/image_event_data.h>

class SimpleReadService : public kpsr::Service
{
public:
    SimpleReadService(kpsr::Environment * environment, kpsr::Subscriber<kpsr::vision_ocv::ImageData> * subscriber)
        : kpsr::Service(environment, "SimpleReadService")
        , _subscriber(subscriber)
    {}

    void start() {
        std::function<void(kpsr::vision_ocv::ImageData)> simpleListener = std::bind(&SimpleReadService::onEventReceived, this, std::placeholders::_1);
        this->_subscriber->registerListener("SimpleReadService", simpleListener);
    }

    void stop() {
        this->_subscriber->removeListener("SimpleReadService");
    }

    void execute() {}

    void onEventReceived(const kpsr::vision_ocv::ImageData & event) {
        spdlog::info("SimpleReadService. event received. {}"
                  ". image type: {}"
                  ". image rows: {}"
                  ". image cols: {}",
                  event.seq,
                  event.img.type(),
                  event.img.rows,
                  event.img.cols
        );
        lastReadImg = event;
        receivedImage = true;
    }

    bool receivedImage = false;
    kpsr::vision_ocv::ImageData lastReadImg;

private:
    kpsr::Subscriber<kpsr::vision_ocv::ImageData> * _subscriber;
    long _startTimestamp;
};

#endif // SIMPLE_READ_SERVICE_H
