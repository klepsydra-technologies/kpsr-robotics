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

#ifndef POSE_EVENT_DATA_ZMQ_SERIALIZER_H
#define POSE_EVENT_DATA_ZMQ_SERIALIZER_H

#include <cereal/cereal.hpp>

#include <cereal/types/vector.hpp>

#include <klepsydra/geometry/pose_event_data.h>

namespace cereal {
template<class Archive>
void serialize(Archive &archive, kpsr::geometry::PoseEventData &event)
{
    archive(CEREAL_NVP(event.frameId),
            CEREAL_NVP(event.seq),
            CEREAL_NVP(event.timestamp),
            CEREAL_NVP(event.eulerAvailable),
            CEREAL_NVP(event.posCovarianceAvailable),
            CEREAL_NVP(event.x),
            CEREAL_NVP(event.y),
            CEREAL_NVP(event.z),
            CEREAL_NVP(event.roll),
            CEREAL_NVP(event.pitch),
            CEREAL_NVP(event.yaw),
            CEREAL_NVP(event.positionCovariance),
            CEREAL_NVP(event.qx),
            CEREAL_NVP(event.qy),
            CEREAL_NVP(event.qz),
            CEREAL_NVP(event.qw));
}
} // namespace cereal
#endif // POSE_EVENT_DATA_ZMQ_SERIALIZER_H
