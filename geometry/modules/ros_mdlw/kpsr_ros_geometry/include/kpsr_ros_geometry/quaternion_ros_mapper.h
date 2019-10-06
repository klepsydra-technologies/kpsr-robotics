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

#ifndef QUATERNION_ROS_MAPPER_H
#define QUATERNION_ROS_MAPPER_H

#include "geometry_msgs/Quaternion.h"

#include <klepsydra/serialization/mapper.h>
#include <klepsydra/geometry/quaternion.h>

namespace kpsr {
template<>
/**
 * @brief The Mapper<kpsr::geometry::Quaternion, geometry_msgs::Quaternion> class
 *
 * @copyright Klepsydra Technologies 2019-2020.
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-geometry-ros-composition
 *
 * @details Geometry object mapper for ROS middleware.
 */
class Mapper<kpsr::geometry::Quaternion, geometry_msgs::Quaternion>
{
public:

   void fromMiddleware(const geometry_msgs::Quaternion & message, kpsr::geometry::Quaternion & event) {
      event.x = message.x;
      event.y = message.y;
      event.z = message.z;
      event.w = message.w;
   }

   void toMiddleware(const kpsr::geometry::Quaternion & event, geometry_msgs::Quaternion & message) {
      message.x = event.x;
      message.y = event.y;
      message.z = event.z;
      message.w = event.w;
   }
};
}
#endif
