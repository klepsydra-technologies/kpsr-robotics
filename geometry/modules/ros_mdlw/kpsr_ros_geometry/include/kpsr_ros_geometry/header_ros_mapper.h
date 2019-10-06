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

#ifndef HEADER_ROS_MAPPER_H
#define HEADER_ROS_MAPPER_H

#include "std_msgs/Header.h"

#include <klepsydra/serialization/mapper.h>
#include <klepsydra/geometry/header.h>

namespace kpsr {
template<>
/**
 * @brief The Mapper<kpsr::geometry::Header, std_msgs::Header> class
 *
 * @copyright Klepsydra Technologies 2019-2020.
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

   void fromMiddleware(const std_msgs::Header & message, kpsr::geometry::Header & event) {
      event.seq = message.seq;
      event.frame_id = message.frame_id;
   }

   void toMiddleware(const kpsr::geometry::Header & event, std_msgs::Header & message) {
      message.seq = event.seq;
      message.frame_id = event.frame_id;
   }
};
}
#endif
