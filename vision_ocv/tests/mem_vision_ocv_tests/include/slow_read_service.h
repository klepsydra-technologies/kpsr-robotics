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

#ifndef SLOW_READ_SERVICE_H
#define SLOW_READ_SERVICE_H

#include <iostream>
#include <thread>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

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
        std::cout << "SlowReadService. event received. " << event.seq
                  << ". image type: " << event.img.type()
                  << ". image rows: " << event.img.rows
                  << ". image cols: " << event.img.cols
                  << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
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
