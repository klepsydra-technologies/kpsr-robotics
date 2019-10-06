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

#ifndef VECTOR3_ROS_MAPPER_H
#define VECTOR3_ROS_MAPPER_H

#include "geometry_msgs/Vector3.h"

#include <klepsydra/serialization/mapper.h>
#include <klepsydra/geometry/vector3.h>

namespace kpsr {
template<>
/**
 * @brief The Mapper<kpsr::geometry::Vector3, geometry_msgs::Vector3> class
 *
 * @copyright Klepsydra Technologies 2019-2020.
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

   void fromMiddleware(const geometry_msgs::Vector3 & message, kpsr::geometry::Vector3 & event) {
      event.x = message.x;
      event.y = message.y;
      event.z = message.z;
   }

   void toMiddleware(const kpsr::geometry::Vector3 & event, geometry_msgs::Vector3 & message) {
      message.x = event.x;
      message.y = event.y;
      message.z = event.z;
   }
};
}
#endif
