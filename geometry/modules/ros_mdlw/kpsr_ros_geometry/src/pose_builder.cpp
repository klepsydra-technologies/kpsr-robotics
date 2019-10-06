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

#include <algorithm>
#include "pose_builder.h"
#include <tf/transform_datatypes.h>

void kpsr::geometry::ros_mdlw::PoseBuilder::createPoseEvent(const char * frameId, double x, double y, double z,
                                                          double qx, double qy, double qz, double qw,
                                                          double * posCovariance, bool calculateEuler,
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

void kpsr::geometry::ros_mdlw::PoseBuilder::createPoseEvent(const char * frameId, float x, float y, float z,
                                                          float qx, float qy, float qz, float qw,
                                                          float * posCovariance, bool calculateEuler,
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

