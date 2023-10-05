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

#ifndef LASER_SCAN_EVENT_SUBSCRIBER_SERVICE_H
#define LASER_SCAN_EVENT_SUBSCRIBER_SERVICE_H

#include <functional>

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"

#include <klepsydra/sdk/service.h>
#include <klepsydra/sdk/subscriber.h>

#include <klepsydra/sensors/laser_scan_event.h>

class LaserScanEventSubscriberService : public kpsr::Service
{
public:
    LaserScanEventSubscriberService(
        kpsr::Environment *environment,
        kpsr::Subscriber<kpsr::sensors::LaserScanEvent> *laserScanEventSubscriber)
        : Service(nullptr, environment, "laserScanEvent_subs_service")
        , _laserScanEventSubscriber(laserScanEventSubscriber)
    {}

    void start()
    {
        std::function<void(kpsr::sensors::LaserScanEvent)> listenerFunction =
            std::bind(&LaserScanEventSubscriberService::onMessageReceived,
                      this,
                      std::placeholders::_1);
        this->_laserScanEventSubscriber->registerListener("laserScanEvent_subs_service",
                                                          listenerFunction);
    }

    void stop() {}
    void execute() {}

    kpsr::sensors::LaserScanEvent sensor;

private:
    void onMessageReceived(const kpsr::sensors::LaserScanEvent &eventData)
    {
        sensor = eventData;
        spdlog::info("LaserScanEventSubscriberService.onMessageReceived. seq: {}"
                     ". eventData.frameId: {}"
                     ". eventData.angle_min: {}"
                     ". eventData.range_min: {}"
                     ". eventData.ranges.size(): {}"
                     ". eventData.ranges[0]: {}"
                     ". eventData.intensities.size(): {}"
                     ". eventData.intensities[0]: {}",
                     eventData.seq,
                     eventData.frameId,
                     eventData.angle_min,
                     eventData.range_min,
                     eventData.ranges.size(),
                     eventData.ranges[0],
                     eventData.intensities.size(),
                     eventData.intensities[0]);
    }

    kpsr::Subscriber<kpsr::sensors::LaserScanEvent> *_laserScanEventSubscriber;
};

#endif // LASER_SCAN_EVENT_SUBSCRIBER_SERVICE_H
