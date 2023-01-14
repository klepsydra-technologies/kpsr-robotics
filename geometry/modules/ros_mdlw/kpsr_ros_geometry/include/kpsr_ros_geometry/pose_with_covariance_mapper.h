/*
 * Copyright 2023 Klepsydra Technologies AG
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef POSE_WITH_COVARIANCE_ROS_MAPPER_H
#define POSE_WITH_COVARIANCE_ROS_MAPPER_H

#include <geometry_msgs/PoseWithCovariance.h>

#include <klepsydra/serialization/mapper.h>
#include <kpsr_ros_geometry/pose_builder.h>

namespace kpsr {
template<>
/**
 * @brief The Mapper<kpsr::geometry::PoseEventData, geometry_msgs::PoseWithCovariance> class
 *
 * @copyright 2023 Klepsydra Technologies AG
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-geometry-ros-composition
 *
 * @details Geometry object mapper for ROS middleware.
 */
class Mapper<kpsr::geometry::PoseEventData, geometry_msgs::PoseWithCovariance>
{
public:
    /**
     * @brief fromMiddleware
     * @param message
     * @param event
     */
    void fromMiddleware(const geometry_msgs::PoseWithCovariance &message,
                        kpsr::geometry::PoseEventData &event)
    {
        kpsr::geometry::ros_mdlw::PoseBuilder::createPoseEvent("",
                                                               message.pose.position.x,
                                                               message.pose.position.y,
                                                               message.pose.position.z,
                                                               message.pose.orientation.x,
                                                               message.pose.orientation.y,
                                                               message.pose.orientation.z,
                                                               message.pose.orientation.w,
                                                               message.covariance.data(),
                                                               true,
                                                               event);
        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch());
        event.timestamp = ms.count();
    }

    /**
     * @brief toMiddleware
     * @param event
     * @param message
     */
    void toMiddleware(const kpsr::geometry::PoseEventData &event,
                      geometry_msgs::PoseWithCovariance &message)
    {
        kpsr::geometry::ros_mdlw::PoseBuilder::createPose(event.x,
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
                                                          message.pose);

        if (event.positionCovariance.size() == 36) {
            std::copy(event.positionCovariance.begin(),
                      event.positionCovariance.end(),
                      message.covariance.begin());
        }
    }
};
} // namespace kpsr
#endif
