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
