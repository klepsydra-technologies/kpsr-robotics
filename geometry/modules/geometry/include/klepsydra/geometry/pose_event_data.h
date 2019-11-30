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

#ifndef POSE_DATA_H
#define POSE_DATA_H

#include <vector>

#include <klepsydra/core/sensor.h>

namespace kpsr
{
namespace geometry
{
/**
 * @brief The PoseEventData struct
 *
 * @copyright Klepsydra Technologies 2019-2020.
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-geometry-application
 *
 * @details Pose specific data. It should be compatible with ROS and Mavlink.
 */
struct PoseEventData : public Sensor
{
    PoseEventData()
    {}

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
    PoseEventData(
            std::string frameId,
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
    PoseEventData(const PoseEventData & that)
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
    void clone(const PoseEventData & that) {
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
}
}
#endif
