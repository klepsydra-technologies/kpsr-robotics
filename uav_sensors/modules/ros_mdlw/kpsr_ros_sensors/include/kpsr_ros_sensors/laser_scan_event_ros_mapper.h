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

#ifndef LASER_SCAN_EVENT_ROS_MAPPER_H
#define LASER_SCAN_EVENT_ROS_MAPPER_H

#include "sensor_msgs/LaserScan.h"

#include <klepsydra/sensors/laser_scan_event.h>
#include <klepsydra/serialization/mapper.h>

namespace kpsr {
template<>
/**
 * @brief The Mapper<kpsr::sensors::LaserScanEvent, sensor_msgs::LaserScan> class
 *
 * @copyright 2023 Klepsydra Technologies AG
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-sensors-composition
 *
 */
class Mapper<kpsr::sensors::LaserScanEvent, sensor_msgs::LaserScan>
{
public:
    void fromMiddleware(const sensor_msgs::LaserScan &message, kpsr::sensors::LaserScanEvent &event)
    {
        event.frameId = message.header.frame_id;
        event.seq = message.header.seq;
        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch());
        event.timestamp = ms.count();

        event.angle_min = message.angle_min;
        event.angle_max = message.angle_max;
        event.angle_increment = message.angle_increment;
        event.time_increment = message.time_increment;
        event.scan_time = message.scan_time;
        event.range_min = message.range_min;
        event.range_max = message.range_max;
        event.ranges = message.ranges;
        event.intensities = message.intensities;
    }

    void toMiddleware(const kpsr::sensors::LaserScanEvent &event, sensor_msgs::LaserScan &message)
    {
        std_msgs::Header header;
        header.seq = event.seq;
        header.stamp = ros::Time::now();
        header.frame_id = event.frameId;

        message.header = header;

        message.angle_min = event.angle_min;
        message.angle_max = event.angle_max;
        message.angle_increment = event.angle_increment;
        message.time_increment = event.time_increment;
        message.scan_time = event.scan_time;
        message.range_min = event.range_min;
        message.range_max = event.range_max;
        message.ranges = event.ranges;
        message.intensities = event.intensities;
    }
};
} // namespace kpsr
#endif
