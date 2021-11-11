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

#ifndef POSITION_TARGET_ROS_MAPPER_H
#define POSITION_TARGET_ROS_MAPPER_H

#include <mavros_msgs/PositionTarget.h>

#include <klepsydra/serialization/mapper.h>
#include <klepsydra/geometry/position_target.h>

namespace kpsr
{
template <>
/**
 * @brief The Mapper<kpsr::geometry::PositionTarget, mavros_msgs::PositionTarget> class
 *
 * @copyright Klepsydra Technologies 2019-2020.
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-geometry-ros-composition
 *
 * @details Geometry object mapper for ROS middleware.
 */
class Mapper<kpsr::geometry::PositionTarget, mavros_msgs::PositionTarget>
{
public:

  /**
   * @brief fromMiddleware
   * @param message
   * @param event
   */
  void fromMiddleware(const mavros_msgs::PositionTarget &message,
                      kpsr::geometry::PositionTarget &event) {
    event.frameId = message.header.frame_id;
    event.seq = message.header.seq;
    std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
    event.timestamp = ms.count();

    event.coordinate_frame = message.coordinate_frame;
    event.type_mask = message.type_mask;
    event.x = message.position.x;
    event.y = message.position.y;
    event.z = message.position.z;
    event.vx = message.velocity.x;
    event.vy = message.velocity.y;
    event.vz = message.velocity.z;
    event.accx = message.acceleration_or_force.x;
    event.accy = message.acceleration_or_force.y;
    event.accz = message.acceleration_or_force.z;
    event.yaw = message.yaw;
    event.yaw_rate = message.yaw_rate;
  }
  /**
   * @brief toMiddleware
   * @param event
   * @param message
   */
  void toMiddleware(const kpsr::geometry::PositionTarget &event,
                    mavros_msgs::PositionTarget &message) {
    
    std_msgs::Header header;
    header.seq = event.seq;
    header.stamp = ros::Time::now();
    header.frame_id = event.frameId;
    message.header = header;

    message.coordinate_frame = event.coordinate_frame;
    message.type_mask = event.type_mask;
    message.position.x = event.x;
    message.position.y = event.y;
    message.position.z = event.z;
    message.velocity.x = event.vx;
    message.velocity.y = event.vy;
    message.velocity.z = event.vz;
    message.acceleration_or_force.x = event.accx;
    message.acceleration_or_force.y = event.accy;
    message.acceleration_or_force.z = event.accz;
    message.yaw = event.yaw;
    message.yaw_rate = event.yaw_rate;

  }
};
}
#endif

