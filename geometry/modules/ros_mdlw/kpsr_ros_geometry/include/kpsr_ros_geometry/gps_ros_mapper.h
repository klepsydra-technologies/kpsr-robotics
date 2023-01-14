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

#ifndef GPS_ROS_MAPPER_H
#define GPS_ROS_MAPPER_H

#include "sensor_msgs/NavSatFix.h"
#include <klepsydra/geometry/gps.h>

namespace kpsr {
template<>
/**
 * @brief The Mapper<kpsr::geometry::Gps, sensor_msgs::NavSatFix> class
 *
 * @copyright 2023 Klepsydra Technologies AG
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-geometry-ros-composition
 *
 * @details Geometry object mapper for ROS middleware.
 */
class Mapper<kpsr::geometry::Gps, sensor_msgs::NavSatFix>
{
public:
    void fromMiddleware(const sensor_msgs::NavSatFix &message, kpsr::geometry::Gps &event)
    {
        event.latitude = message.latitude;
        event.longitude = message.longitude;
        event.altitude = message.altitude;
    }

    void toMiddleware(const kpsr::geometry::Gps &event, sensor_msgs::NavSatFix &message)
    {
        message.latitude = event.latitude;
        message.longitude = event.longitude;
        message.altitude = event.altitude;
    }
};
} // namespace kpsr
#endif
