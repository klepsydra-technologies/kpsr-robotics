// Copyright 2023 Klepsydra Technologies AG
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "pose_builder.h"
#include <algorithm>
#include <tf/transform_datatypes.h>

void kpsr::geometry::ros_mdlw::PoseBuilder::createPoseEvent(
    const std::string &frameId,
    double x,
    double y,
    double z,
    double qx,
    double qy,
    double qz,
    double qw,
    const double *posCovariance,
    bool calculateEuler,
    kpsr::geometry::PoseEventData &poseEventData)
{
    poseEventData.frameId = frameId;

    poseEventData.qx = qx;
    poseEventData.qy = qy;
    poseEventData.qz = qz;
    poseEventData.qw = qw;

    if (calculateEuler) {
        tf::Quaternion q(qx, qy, qz, qw);
        tf::Matrix3x3 m(q);
        double roll, pitch, yaw;
        m.getRPY(roll, pitch, yaw);

        poseEventData.roll = roll;
        poseEventData.pitch = pitch;
        poseEventData.yaw = yaw;

        poseEventData.eulerAvailable = true;
    } else {
        poseEventData.eulerAvailable = false;
    }

    poseEventData.x = x;
    poseEventData.y = y;
    poseEventData.z = z;

    if (posCovariance != NULL) {
        poseEventData.positionCovariance.resize(36);
        memcpy(&poseEventData.positionCovariance[0], posCovariance, 36 * sizeof(double));
        poseEventData.posCovarianceAvailable = true;
    } else {
        poseEventData.posCovarianceAvailable = false;
    }
}

void kpsr::geometry::ros_mdlw::PoseBuilder::createPoseEvent(
    const std::string &frameId,
    float x,
    float y,
    float z,
    float qx,
    float qy,
    float qz,
    float qw,
    const float *posCovariance,
    bool calculateEuler,
    kpsr::geometry::PoseEventData &poseEventData)
{
    poseEventData.frameId = frameId;

    poseEventData.qx = qx;
    poseEventData.qy = qy;
    poseEventData.qz = qz;
    poseEventData.qw = qw;

    if (calculateEuler) {
        tf::Quaternion q(qx, qy, qz, qw);
        tf::Matrix3x3 m(q);
        double roll, pitch, yaw;
        m.getRPY(roll, pitch, yaw);

        poseEventData.roll = roll;
        poseEventData.pitch = pitch;
        poseEventData.yaw = yaw;

        poseEventData.eulerAvailable = true;
    } else {
        poseEventData.eulerAvailable = false;
    }

    poseEventData.x = x;
    poseEventData.y = y;
    poseEventData.z = z;

    if (posCovariance != NULL) {
        poseEventData.positionCovariance.resize(36);
        memcpy(&poseEventData.positionCovariance[0], posCovariance, 36 * sizeof(double));
        poseEventData.posCovarianceAvailable = true;
    } else {
        poseEventData.posCovarianceAvailable = false;
    }
}

void kpsr::geometry::ros_mdlw::PoseBuilder::createPose(float x,
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
                                                       geometry_msgs::Pose &poseData)
{
    poseData.position.x = x;
    poseData.position.y = y;
    poseData.position.z = z;

    if (calculateQuaternion) {
        tf::Quaternion quaternion;
        quaternion.setRPY(roll, pitch, yaw);
        poseData.orientation.x = quaternion.x();
        poseData.orientation.y = quaternion.y();
        poseData.orientation.z = quaternion.z();
        poseData.orientation.w = quaternion.w();
    } else {
        poseData.orientation.x = qx;
        poseData.orientation.y = qy;
        poseData.orientation.z = qz;
        poseData.orientation.w = qw;
    }
}

void kpsr::geometry::ros_mdlw::PoseBuilder::createPose(double x,
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
                                                       geometry_msgs::Pose &poseData)
{
    poseData.position.x = x;
    poseData.position.y = y;
    poseData.position.z = z;

    if (calculateQuaternion) {
        tf::Quaternion quaternion;
        quaternion.setRPY(roll, pitch, yaw);
        poseData.orientation.x = quaternion.x();
        poseData.orientation.y = quaternion.y();
        poseData.orientation.z = quaternion.z();
        poseData.orientation.w = quaternion.w();
    } else {
        poseData.orientation.x = qx;
        poseData.orientation.y = qy;
        poseData.orientation.z = qz;
        poseData.orientation.w = qw;
    }
}
