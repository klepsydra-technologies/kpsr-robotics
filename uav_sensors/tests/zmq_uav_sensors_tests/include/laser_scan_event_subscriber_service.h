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

#ifndef LASER_SCAN_EVENT_SUBSCRIBER_SERVICE_H
#define LASER_SCAN_EVENT_SUBSCRIBER_SERVICE_H

#include <iostream>
#include <functional>

#include <klepsydra/core/service.h>
#include <klepsydra/core/subscriber.h>

#include <klepsydra/sensors/laser_scan_event.h>

class LaserScanEventSubscriberService : public kpsr::Service {
public:
    LaserScanEventSubscriberService(kpsr::Environment * environment,
                                 kpsr::Subscriber<kpsr::sensors::LaserScanEvent> * laserScanEventSubscriber)
        : Service(environment, "laserScanEvent_subs_service"), _laserScanEventSubscriber(laserScanEventSubscriber) {
    }

    void start() {
        std::function<void(kpsr::sensors::LaserScanEvent)> listenerFunction = std::bind(&LaserScanEventSubscriberService::onMessageReceived, this, std::placeholders::_1);
        this->_laserScanEventSubscriber->registerListener("laserScanEvent_subs_service", listenerFunction);
    }

    void stop() {}
    void execute() {}

    kpsr::sensors::LaserScanEvent sensor;

private:

    void onMessageReceived(const kpsr::sensors::LaserScanEvent & eventData) {
        sensor = eventData;
        std::cout << "LaserScanEventSubscriberService.onMessageReceived. seq: " << eventData.seq
                  << ". eventData.frameId: " << eventData.frameId
                  << ". eventData.angle_min: " << eventData.angle_min
                  << ". eventData.range_min: " << eventData.range_min
                  << ". eventData.ranges.size(): " << eventData.ranges.size()
                  << ". eventData.ranges[0]: " << eventData.ranges[0]
                  << ". eventData.intensities.size(): " << eventData.intensities.size()
                  << ". eventData.intensities[0]: " << eventData.intensities[0] << std::endl;
    }

    kpsr::Subscriber<kpsr::sensors::LaserScanEvent> * _laserScanEventSubscriber;
};

#endif // LASER_SCAN_EVENT_SUBSCRIBER_SERVICE_H
