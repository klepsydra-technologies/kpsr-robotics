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

#ifndef POSE_EVENT_DATA_SUBSCRIBER_SERVICE_H
#define POSE_EVENT_DATA_SUBSCRIBER_SERVICE_H

#include <functional>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

#include <klepsydra/core/service.h>
#include <klepsydra/core/subscriber.h>
#include <klepsydra/geometry/pose_event_data.h>

class PoseEventDataSubscriberService : public kpsr::Service {
public:
    PoseEventDataSubscriberService(kpsr::Environment * environment,
                                 kpsr::Subscriber<kpsr::geometry::PoseEventData> * poseEventDataSubscriber)
        : Service(environment, "poseEventData_subs_service"), _poseEventDataSubscriber(poseEventDataSubscriber) {
    }

    void start() {
        std::function<void(kpsr::geometry::PoseEventData)> listenerFunction = std::bind(&PoseEventDataSubscriberService::onMessageReceived, this, std::placeholders::_1);
        this->_poseEventDataSubscriber->registerListener("poseEventData_subs_service", listenerFunction);
    }

    void stop() {}
    void execute() {}

    kpsr::geometry::PoseEventData sensor;

private:

    void onMessageReceived(const kpsr::geometry::PoseEventData & eventData) {
        spdlog::info("PoseEventDataSubscriberService.onMessageReceived.");
        sensor = eventData;
    }

    kpsr::Subscriber<kpsr::geometry::PoseEventData> * _poseEventDataSubscriber;
};

#endif // POSE_EVENT_DATA_SUBSCRIBER_SERVICE_H
