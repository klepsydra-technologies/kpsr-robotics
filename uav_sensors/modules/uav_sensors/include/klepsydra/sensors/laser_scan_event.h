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

#ifndef KPSR_SENSORS_LASER_SCAN_EVENT_H_
#define KPSR_SENSORS_LASER_SCAN_EVENT_H_


// Include section.
#include <vector>

#include <klepsydra/core/sensor.h>

namespace kpsr {
namespace sensors {
/**
 * @brief The LaserScanEvent struct
 *
 * @copyright Klepsydra Technologies 2019-2020.
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-sensors-application
 *
 */
class LaserScanEvent : public Sensor {
public:
    /**
    * @brief LaserScanEvent
    */
    LaserScanEvent() {}

    /**
     * @brief LaserScanEvent
     * @param frameId
     * @param seq
     * @param angle_min
     * @param angle_max
     * @param angle_increment
     * @param time_increment
     * @param scan_time
     * @param range_min
     * @param range_max
     * @param ranges
     * @param intensities
     */
    LaserScanEvent(
            std::string frameId,
            int seq,
            long timestamp,
            float angle_min,
            float angle_max,
            float angle_increment,
            float time_increment,
            float scan_time,
            float range_min,
            float range_max,
            std::vector<float> ranges,
            std::vector<float> intensities)
        : Sensor(frameId, seq, timestamp)
        , angle_min(angle_min)
        , angle_max(angle_max)
        , angle_increment(angle_increment)
        , time_increment(time_increment)
        , scan_time(scan_time)
        , range_min(range_min)
        , range_max(range_max)
        , ranges(ranges)
        , intensities(intensities)
    {}

    /**
     * @brief LaserScanEvent
     * @param that
     */
    LaserScanEvent(const LaserScanEvent & that)
        : Sensor(that.frameId, that.seq, that.timestamp)
        , angle_min(that.angle_min)
        , angle_max(that.angle_max)
        , angle_increment(that.angle_increment)
        , time_increment(that.time_increment)
        , scan_time(that.scan_time)
        , range_min(that.range_min)
        , range_max(that.range_max)
        , ranges(that.ranges)
        , intensities(that.intensities)
    {}

    /**
     * @brief clone
     * @param that
     */
    void clone(const LaserScanEvent & that) {
        Sensor::clone(that);
        this->angle_min = that.angle_min;
        this->angle_max = that.angle_max;
        this->angle_increment = that.angle_increment;
        this->time_increment = that.time_increment;
        this->scan_time = that.scan_time;
        this->range_min = that.range_min;
        this->range_max = that.range_max;
        this->ranges = that.ranges;
        this->intensities = that.intensities;
    }

    /**
     * @brief angle_min
     */
    float angle_min;
    /**
     * @brief angle_max
     */
    float angle_max;
    /**
     * @brief angle_increment
     */
    float angle_increment;
    /**
     * @brief time_increment
     */
    float time_increment;
    /**
     * @brief scan_time
     */
    float scan_time;
    /**
     * @brief range_min
     */
    float range_min;
    /**
     * @brief range_max
     */
    float range_max;
    /**
     * @brief ranges
     */
    std::vector<float> ranges;
    /**
     * @brief intensities
     */
    std::vector<float> intensities;
};
}
}
#endif
