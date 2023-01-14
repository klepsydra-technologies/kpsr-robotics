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

#ifndef POSE_BUILDER_H
#define POSE_BUILDER_H

#include <klepsydra/core/environment.h>
#include <klepsydra/geometry/pose_event_data.h>

#include <geometry_msgs/Pose.h>

namespace kpsr {
namespace geometry {
namespace ros_mdlw {
/**
 * @brief The PoseBuilder class
 *
 * @copyright 2023 Klepsydra Technologies AG
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-geometry-ros-internal
 *
 * @details Facility class to create pose events.
 */
class PoseBuilder
{
public:
    /**
     * @brief createPoseEvent
     * @param frameId
     * @param x
     * @param y
     * @param z
     * @param qx
     * @param qy
     * @param qz
     * @param qw
     * @param covariance
     * @param calculateEuler
     * @param poseEventData
     */
    static void createPoseEvent(const std::string &frameId,
                                double x,
                                double y,
                                double z,
                                double qx,
                                double qy,
                                double qz,
                                double qw,
                                const double *covariance,
                                bool calculateEuler,
                                PoseEventData &poseEventData);

    /**
     * @brief createPoseEvent
     * @param frameId
     * @param x
     * @param y
     * @param z
     * @param qx
     * @param qy
     * @param qz
     * @param qw
     * @param covariance
     * @param calculateEuler
     * @param poseEventData
     */
    static void createPoseEvent(const std::string &frameId,
                                float x,
                                float y,
                                float z,
                                float qx,
                                float qy,
                                float qz,
                                float qw,
                                const float *covariance,
                                bool calculateEuler,
                                PoseEventData &poseEventData);

    /**
     * @brief createPose
     * @param x
     * @param y
     * @param z
     * @param qx
     * @param qy
     * @param qz
     * @param qw
     * @param roll
     * @param pitch
     * @param yaw
     * @param calculateQuaternion
     * @param poseEventData
     */
    static void createPose(double x,
                           double y,
                           double z,
                           double qx,
                           double qy,
                           double qz,
                           double qw,
                           double roll,
                           double pitch,
                           double yaw,
                           bool calculateQuaternion,
                           geometry_msgs::Pose &poseData);

    /**
     * @brief createPose
     * @param x
     * @param y
     * @param z
     * @param qx
     * @param qy
     * @param qz
     * @param qw
     * @param roll
     * @param pitch
     * @param yaw
     * @param calculateQuaternion
     * @param poseEventData
     */
    static void createPose(float x,
                           float y,
                           float z,
                           float qx,
                           float qy,
                           float qz,
                           float qw,
                           float roll,
                           float pitch,
                           float yaw,
                           bool calculateQuaternion,
                           geometry_msgs::Pose &poseData);
};
} // namespace ros_mdlw
} // namespace geometry
} // namespace kpsr
#endif
