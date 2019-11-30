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
