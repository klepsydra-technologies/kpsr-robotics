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

#include <algorithm>
#include "pose_builder.h"
#include <tf/transform_datatypes.h>

void kpsr::geometry::ros_mdlw::PoseBuilder::createPoseEvent(const std::string& frameId, double x, double y, double z,
                                                            double qx, double qy, double qz, double qw,
                                                            const double * posCovariance, bool calculateEuler,
                                                            kpsr::geometry::PoseEventData & poseEventData) {

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
    }
    else {
        poseEventData.eulerAvailable = false;
    }

    poseEventData.x = x;
    poseEventData.y = y;
    poseEventData.z = z;

    if (posCovariance != NULL) {
        poseEventData.positionCovariance.resize(36);
        memcpy(&poseEventData.positionCovariance[0], posCovariance, 36*sizeof(double));
        poseEventData.posCovarianceAvailable = true;
    }
    else {
        poseEventData.posCovarianceAvailable = false;
    }
}

void kpsr::geometry::ros_mdlw::PoseBuilder::createPoseEvent(const std::string& frameId, float x, float y, float z,
                                                          float qx, float qy, float qz, float qw,
                                                          const float * posCovariance, bool calculateEuler,
                                                          kpsr::geometry::PoseEventData & poseEventData) {
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
    }
    else {
        poseEventData.eulerAvailable = false;
    }

    poseEventData.x = x;
    poseEventData.y = y;
    poseEventData.z = z;

    if (posCovariance != NULL) {
        poseEventData.positionCovariance.resize(36);
        memcpy(&poseEventData.positionCovariance[0], posCovariance, 36*sizeof(double));
        poseEventData.posCovarianceAvailable = true;
    }
    else {
        poseEventData.posCovarianceAvailable = false;
    }
}

void kpsr::geometry::ros_mdlw::PoseBuilder::createPose(float x, float y, float z,
                                                       float qx, float qy, float qz, float qw,
                                                       float roll, float pitch, float yaw,
                                                       bool calculateQuaternion,
                                                       geometry_msgs::Pose & poseData) {

   
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

void kpsr::geometry::ros_mdlw::PoseBuilder::createPose(double x, double y, double z,
                                                       double qx, double qy, double qz, double qw,
                                                       double roll, double pitch, double yaw,
                                                       bool calculateQuaternion,
                                                       geometry_msgs::Pose & poseData) {

   
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
