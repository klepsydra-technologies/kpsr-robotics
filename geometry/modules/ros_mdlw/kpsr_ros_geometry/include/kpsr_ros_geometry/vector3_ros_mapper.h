/****************************************************************************
*
*                           Klepsydra Core Modules
*              Copyright (C) 2019-2020  Klepsydra Technologies GmbH
*                            All Rights Reserved.
*
*  This file is subject to the terms and conditions defined in
*  file 'LICENSE.md', which is part of this source code package.
*
*  NOTICE:  All information contained herein is, and remains the property of Klepsydra
*  Technologies GmbH and its suppliers, if any. The intellectual and technical concepts
*  contained herein are proprietary to Klepsydra Technologies GmbH and its suppliers and
*  may be covered by Swiss and Foreign Patents, patents in process, and are protected by
*  trade secret or copyright law. Dissemination of this information or reproduction of
*  this material is strictly forbidden unless prior written permission is obtained from
*  Klepsydra Technologies GmbH.
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
