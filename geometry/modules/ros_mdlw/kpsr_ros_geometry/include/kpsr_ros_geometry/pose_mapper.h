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
                    NULL,
                    message.position.x,
                    message.position.y,
                    message.position.z,
                    message.orientation.x,
                    message.orientation.y,
                    message.orientation.z,
                    message.orientation.w,
                    NULL, true, event);
        event.frameId = message.header.frame_id;
        event.seq = message.header.seq;
        std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
        event.timestamp = ms.count();
    }

    /**
     * @brief toMiddleware
     * @param event
     * @param message
     */
    void toMiddleware(const kpsr::geometry::PoseEventData & event, geometry_msgs::Pose & message) {
        std_msgs::Header header;
        header.seq = event.seq;
        header.stamp = ros::Time::now();
        header.frame_id = event.frameId;

        geometry_msgs::Point point;
        point.x = event.x;
        point.y = event.y;
        point.z = event.z;

        geometry_msgs::Quaternion quaternion;
        quaternion.x = event.qx;
        quaternion.y = event.qy;
        quaternion.z = event.qz;
        quaternion.w = event.qw;

        message.header = header;
        message.position = point;
        message.orientation = quaternion;
    }
};
}
#endif
