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

#ifndef VECTOR3_ROS_MAPPER_H
#define VECTOR3_ROS_MAPPER_H

#include "geometry_msgs/Vector3.h"

#include <klepsydra/geometry/vector3.h>
#include <klepsydra/serialization/mapper.h>

namespace kpsr {
template<>
/**
 * @brief The Mapper<kpsr::geometry::Vector3, geometry_msgs::Vector3> class
 *
 * @copyright 2023 Klepsydra Technologies AG
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-geometry-ros-composition
 *
 * @details Geometry object mapper for ROS middleware.
 */
class Mapper<kpsr::geometry::Vector3, geometry_msgs::Vector3>
{
public:
    void fromMiddleware(const geometry_msgs::Vector3 &message, kpsr::geometry::Vector3 &event)
    {
        event.x = message.x;
        event.y = message.y;
        event.z = message.z;
    }

    void toMiddleware(const kpsr::geometry::Vector3 &event, geometry_msgs::Vector3 &message)
    {
        message.x = event.x;
        message.y = event.y;
        message.z = event.z;
    }
};
} // namespace kpsr
#endif
