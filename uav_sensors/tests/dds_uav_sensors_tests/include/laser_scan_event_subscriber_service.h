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

#ifndef LASER_SCAN_EVENT_SUBSCRIBER_SERVICE_H
#define LASER_SCAN_EVENT_SUBSCRIBER_SERVICE_H

#include <functional>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

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
                  eventData.intensities[0]
        );
    }

    kpsr::Subscriber<kpsr::sensors::LaserScanEvent> * _laserScanEventSubscriber;
};

#endif // LASER_SCAN_EVENT_SUBSCRIBER_SERVICE_H
