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

#ifndef POSE_EVENT_DATA_DDS_MAPPER_H
#define POSE_EVENT_DATA_DDS_MAPPER_H

#include <pose_event.hpp>

#include <klepsydra/serialization/mapper.h>

#include <klepsydra/geometry/pose_event_data.h>

namespace kpsr {
template<>
/**
 * @brief The Mapper<kpsr::geometry::PoseEventData, kpsr_dds_geometry::PoseEventData> class
 *
 * @copyright 2023 Klepsydra Technologies AG
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-geometry-dds-composition
 *
 * @details Geometry object mapper for DDS middleware
 */
class Mapper<kpsr::geometry::PoseEventData, kpsr_dds_geometry::PoseEventData>
{
public:
    /**
     * @brief fromMiddleware
     * @param message
     * @param event
     */
    void fromMiddleware(const kpsr_dds_geometry::PoseEventData &message,
                        kpsr::geometry::PoseEventData &event)
    {
        event.frameId = message.frameId();
        event.seq = message.seq();
        event.timestamp = message.timestamp();

        event.eulerAvailable = message.eulerAvailable();
        event.posCovarianceAvailable = message.posCovarianceAvailable();

        event.x = message.x();
        event.y = message.y();
        event.z = message.z();

        event.roll = message.roll();
        event.pitch = message.pitch();
        event.yaw = message.yaw();

        event.qx = message.qx();
        event.qy = message.qy();
        event.qz = message.qz();
        event.qw = message.qw();

        event.positionCovariance.resize(message.positionCovariance().size());
        std::transform(message.positionCovariance().begin(),
                       message.positionCovariance().end(),
                       event.positionCovariance.begin(),
                       [](const double eventItem) { return eventItem; });
    }

    /**
     * @brief toMiddleware
     * @param event
     * @param message
     */
    void toMiddleware(const kpsr::geometry::PoseEventData &event,
                      kpsr_dds_geometry::PoseEventData &message)
    {
        message.seq(event.seq);
        message.timestamp(event.timestamp);
        message.frameId(event.frameId);

        message.eulerAvailable(event.eulerAvailable);
        message.posCovarianceAvailable(event.posCovarianceAvailable);

        message.x(event.x);
        message.y(event.y);
        message.z(event.z);

        message.roll(event.roll);
        message.pitch(event.pitch);
        message.yaw(event.yaw);

        message.qx(event.qx);
        message.qy(event.qy);
        message.qz(event.qz);
        message.qw(event.qw);

        message.positionCovariance().resize(event.positionCovariance.size());
        std::transform(event.positionCovariance.begin(),
                       event.positionCovariance.end(),
                       message.positionCovariance().begin(),
                       [&](double eventData) { return eventData; });
    }
};
} // namespace kpsr
#endif // POSE_EVENT_DATA_DDS_MAPPER_H
