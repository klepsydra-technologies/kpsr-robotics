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

#ifndef GPS_ROS_MAPPER_H
#define GPS_ROS_MAPPER_H

#include "sensor_msgs/NavSatFix.h"
#include <klepsydra/geometry/gps.h>

namespace kpsr {
template <>
/**
 * @brief The Mapper<kpsr::geometry::Gps, sensor_msgs::NavSatFix> class
 *
 * @copyright Klepsydra Technologies 2019-2020.
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-geometry-ros-composition
 *
 * @details Geometry object mapper for ROS middleware.
 */
class Mapper<kpsr::geometry::Gps, sensor_msgs::NavSatFix> {
public:
  void fromMiddleware(const sensor_msgs::NavSatFix &message,
                      kpsr::geometry::Gps &event) {
    event.latitude = message.latitude;
    event.longitude = message.longitude;
    event.altitude = message.altitude;
  }

  void toMiddleware(const kpsr::geometry::Gps &event,
                    sensor_msgs::NavSatFix &message) {
    message.latitude = event.latitude;
    message.longitude = event.longitude;
    message.altitude = event.altitude;
  }
};
}
#endif
