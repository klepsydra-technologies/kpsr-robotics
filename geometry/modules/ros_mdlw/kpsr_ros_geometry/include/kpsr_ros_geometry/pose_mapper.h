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

#ifndef POSE_ROS_MAPPER_H
#define POSE_ROS_MAPPER_H

#include <geometry_msgs/Pose.h>

#include <klepsydra/serialization/mapper.h>
#include <kpsr_ros_geometry/pose_builder.h>

namespace kpsr
{
template<>
/**
 * @brief The Mapper<kpsr::geometry::PoseEventData, geometry_msgs::Pose> class
 *
 * @copyright Klepsydra Technologies 2019-2020.
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-geometry-ros-composition
 *
 * @details Geometry object mapper for ROS middleware.
 */
class Mapper<kpsr::geometry::PoseEventData, geometry_msgs::Pose>
{
public:
    /**
     * @brief fromMiddleware
     * @param message
     * @param event
     */
    void fromMiddleware(const geometry_msgs::Pose & message, kpsr::geometry::PoseEventData & event) {
        kpsr::geometry::ros_mdlw::PoseBuilder::createPoseEvent(
                    "",
                    message.position.x,
                    message.position.y,
                    message.position.z,
                    message.orientation.x,
                    message.orientation.y,
                    message.orientation.z,
                    message.orientation.w,
                    NULL, true, event);
        std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
        event.timestamp = ms.count();
    }

    /**
     * @brief toMiddleware
     * @param event
     * @param message
     */
    void toMiddleware(const kpsr::geometry::PoseEventData & event, geometry_msgs::Pose & message) {
        kpsr::geometry::ros_mdlw::PoseBuilder::createPose(
            event.x,
            event.y,
            event.z,
            event.qx,
            event.qy,
            event.qz,
            event.qw,
            event.roll,
            event.pitch,
            event.yaw,
            true,
            message);

    }
};
}
#endif
