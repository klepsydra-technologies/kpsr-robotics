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

#ifndef POSE_EVENT_DATA_SUBSCRIBER_SERVICE_H
#define POSE_EVENT_DATA_SUBSCRIBER_SERVICE_H

#include <functional>

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"

#include <klepsydra/geometry/pose_event_data.h>
#include <klepsydra/sdk/service.h>
#include <klepsydra/sdk/subscriber.h>

class PoseEventDataSubscriberService : public kpsr::Service
{
public:
    PoseEventDataSubscriberService(
        kpsr::Environment *environment,
        kpsr::Subscriber<kpsr::geometry::PoseEventData> *poseEventDataSubscriber)
        : Service(nullptr, environment, "poseEventData_subs_service")
        , _poseEventDataSubscriber(poseEventDataSubscriber)
    {}

    void start()
    {
        std::function<void(kpsr::geometry::PoseEventData)> listenerFunction =
            std::bind(&PoseEventDataSubscriberService::onMessageReceived,
                      this,
                      std::placeholders::_1);
        this->_poseEventDataSubscriber->registerListener("poseEventData_subs_service",
                                                         listenerFunction);
    }

    void stop() {}
    void execute() {}

    kpsr::geometry::PoseEventData sensor;

private:
    void onMessageReceived(const kpsr::geometry::PoseEventData &eventData)
    {
        spdlog::info("PoseEventDataSubscriberService.onMessageReceived.");
        sensor = eventData;
    }

    kpsr::Subscriber<kpsr::geometry::PoseEventData> *_poseEventDataSubscriber;
};

#endif // POSE_EVENT_DATA_SUBSCRIBER_SERVICE_H
