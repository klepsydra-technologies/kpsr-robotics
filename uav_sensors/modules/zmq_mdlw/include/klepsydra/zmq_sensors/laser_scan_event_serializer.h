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

#ifndef LASER_SCAN_EVENT_ZMQ_SERIALIZER_H
#define LASER_SCAN_EVENT_ZMQ_SERIALIZER_H

#include <cereal/cereal.hpp>

#include <cereal/types/vector.hpp>

#include <klepsydra/sensors/laser_scan_event.h>

namespace cereal {
template<class Archive>
void serialize(Archive &archive, kpsr::sensors::LaserScanEvent &event)
{
    archive(CEREAL_NVP(event.frameId),
            CEREAL_NVP(event.seq),
            CEREAL_NVP(event.timestamp),
            CEREAL_NVP(event.angle_min),
            CEREAL_NVP(event.angle_max),
            CEREAL_NVP(event.angle_increment),
            CEREAL_NVP(event.time_increment),
            CEREAL_NVP(event.scan_time),
            CEREAL_NVP(event.range_min),
            CEREAL_NVP(event.range_max),
            CEREAL_NVP(event.ranges),
            CEREAL_NVP(event.intensities));
}
} // namespace cereal
#endif // LASER_SCAN_EVENT_ZMQ_SERIALIZER_H
