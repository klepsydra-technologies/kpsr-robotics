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

#ifndef HEADER_ROS_MAPPER_H
#define HEADER_ROS_MAPPER_H

#include "std_msgs/Header.h"

#include <klepsydra/geometry/header.h>
#include <klepsydra/serialization/mapper.h>

namespace kpsr {
template<>
/**
 * @brief The Mapper<kpsr::geometry::Header, std_msgs::Header> class
 *
 * @copyright 2023 Klepsydra Technologies AG
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-geometry-ros-composition
 *
 * @details Geometry object mapper for ROS middleware.
 */
class Mapper<kpsr::geometry::Header, std_msgs::Header>
{
public:
    void fromMiddleware(const std_msgs::Header &message, kpsr::geometry::Header &event)
    {
        event.seq = message.seq;
        event.frame_id = message.frame_id;
    }

    void toMiddleware(const kpsr::geometry::Header &event, std_msgs::Header &message)
    {
        message.seq = event.seq;
        message.frame_id = event.frame_id;
    }
};
} // namespace kpsr
#endif
