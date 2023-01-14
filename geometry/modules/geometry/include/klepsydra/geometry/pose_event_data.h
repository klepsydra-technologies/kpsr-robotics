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

#ifndef POSE_DATA_H
#define POSE_DATA_H

#include <vector>

#include <klepsydra/core/sensor.h>

namespace kpsr {
namespace geometry {
/**
 * @brief The PoseEventData struct
 *
 * @copyright 2023 Klepsydra Technologies AG
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-geometry-application
 *
 * @details Pose specific data. It should be compatible with ROS and Mavlink.
 */
struct PoseEventData : public Sensor
{
    PoseEventData() {}

    /**
     * @brief PoseEventData
     * @param frameId
     * @param seq
     * @param eulerAvailable
     * @param posCovarianceAvailable
     * @param x
     * @param y
     * @param z
     * @param roll
     * @param pitch
     * @param yaw
     * @param qx
     * @param qy
     * @param qz
     * @param qw
     * @param positionCovariance
     */
    PoseEventData(const std::string &frameId,
                  int seq,
                  bool eulerAvailable,
                  bool posCovarianceAvailable,
                  double x,
                  double y,
                  double z,
                  double roll,
                  double pitch,
                  double yaw,
                  double qx,
                  double qy,
                  double qz,
                  double qw,
                  std::vector<double> positionCovariance)
        : Sensor(frameId, seq)
        , eulerAvailable(eulerAvailable)
        , posCovarianceAvailable(posCovarianceAvailable)
        , x(x)
        , y(y)
        , z(z)
        , roll(roll)
        , pitch(pitch)
        , yaw(yaw)
        , qx(qx)
        , qy(qy)
        , qz(qz)
        , qw(qw)
        , positionCovariance(positionCovariance)
    {}

    /**
     * @brief PoseEventData
     * @param that
     */
    PoseEventData(const PoseEventData &that)
        : Sensor(that)
        , eulerAvailable(that.eulerAvailable)
        , posCovarianceAvailable(that.posCovarianceAvailable)
        , x(that.x)
        , y(that.y)
        , z(that.z)
        , roll(that.roll)
        , pitch(that.pitch)
        , yaw(that.yaw)
        , qx(that.qx)
        , qy(that.qy)
        , qz(that.qz)
        , qw(that.qw)
        , positionCovariance(that.positionCovariance)
    {}

    /**
     * @brief clone
     * @param that
     */
    void clone(const PoseEventData &that)
    {
        Sensor::clone(that);

        eulerAvailable = that.eulerAvailable;
        posCovarianceAvailable = that.posCovarianceAvailable;
        x = that.x;
        y = that.y;
        z = that.z;

        roll = that.roll;
        pitch = that.pitch;
        yaw = that.yaw;

        qx = that.qx;
        qy = that.qy;
        qz = that.qz;
        qw = that.qw;

        positionCovariance = that.positionCovariance;
    }

    /**
     * @brief eulerAvailable
     */
    bool eulerAvailable;
    /**
     * @brief posCovarianceAvailable
     */
    bool posCovarianceAvailable;

    /**
     * @brief x
     */
    double x;
    /**
     * @brief y
     */
    double y;
    /**
     * @brief z
     */
    double z;

    /**
     * @brief roll
     */
    double roll;
    /**
     * @brief pitch
     */
    double pitch;
    /**
     * @brief yaw
     */
    double yaw;

    /**
     * @brief qx
     */
    double qx;
    /**
     * @brief qy
     */
    double qy;
    /**
     * @brief qz
     */
    double qz;
    /**
     * @brief qw
     */
    double qw;

    /**
     * @brief positionCovariance
     */
    std::vector<double> positionCovariance;
};
} // namespace geometry
} // namespace kpsr
#endif
