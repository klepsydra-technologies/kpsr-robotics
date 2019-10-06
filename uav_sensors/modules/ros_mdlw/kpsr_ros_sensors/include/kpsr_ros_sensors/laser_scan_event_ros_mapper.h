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

#ifndef LASER_SCAN_EVENT_ROS_MAPPER_H
#define LASER_SCAN_EVENT_ROS_MAPPER_H

#include "sensor_msgs/LaserScan.h"

#include <klepsydra/serialization/mapper.h>
#include <klepsydra/sensors/laser_scan_event.h>

namespace kpsr {
template<>
/**
 * @brief The Mapper<kpsr::sensors::LaserScanEvent, sensor_msgs::LaserScan> class
 *
 * @copyright Klepsydra Technologies 2019-2020.
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-sensors-composition
 *
 */
class Mapper<kpsr::sensors::LaserScanEvent, sensor_msgs::LaserScan>
{
public:

    void fromMiddleware(const sensor_msgs::LaserScan & message, kpsr::sensors::LaserScanEvent & event) {
        event.frameId = message.header.frame_id;
        event.seq = message.header.seq;
        std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
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

    void toMiddleware(const kpsr::sensors::LaserScanEvent & event, sensor_msgs::LaserScan & message) {
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
}
#endif
