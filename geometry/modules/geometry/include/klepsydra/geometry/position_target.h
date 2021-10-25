#ifndef POSITION_TARGET_H
#define POSITION_TARGET_H

#include <vector>
#include <cstdint>
#include <klepsydra/core/sensor.h>

namespace kpsr
{
namespace geometry
{

enum PositionTargetEnum {
    FRAME_LOCAL_NED = 1u,
    FRAME_LOCAL_OFFSET_NED = 7u,
    FRAME_BODY_NED = 8u,
    FRAME_BODY_OFFSET_NED = 9u,
    IGNORE_PX = 1u,
    IGNORE_PY = 2u,
    IGNORE_PZ = 4u,
    IGNORE_VX = 8u,
    IGNORE_VY = 16u,
    IGNORE_VZ = 32u,
    IGNORE_AFX = 64u,
    IGNORE_AFY = 128u,
    IGNORE_AFZ = 256u,
    FORCE = 512u,
    IGNORE_YAW = 1024u,
    IGNORE_YAW_RATE = 2048u,
};

/**
 * @brief The PositionTarget struct
 *
 * @ingroup kpsr-geometry-application
 *
 * @details Msg to set position in target local NED, compatible with mavros.
 */
struct PositionTarget : public Sensor
{
    PositionTarget()
    {}

    /**
     * @brief PositionTarget
     * @param frameId
     * @param seq
     * @param coordinate_frame
     * @param type_mask
     * @param x
     * @param y
     * @param z
     * @param vx
     * @param vy
     * @param vz
     * @param accx
     * @param accy
     * @param accz
     * @param yaw
     * @param yaw_rate
     */
    PositionTarget(
            std::string frameId,
            int seq,
            int coordinate_frame,
            int type_mask,
            double x,
            double y,
            double z,
            double vx,
            double vy,
            double vz,
            double accx,
            double accy,
            double accz,
            float yaw,
            float yaw_rate)
        : Sensor(frameId, seq)
        , coordinate_frame(coordinate_frame)
        , type_mask(type_mask)
        , x(x)
        , y(y)
        , z(z)
        , vx(vx)
        , vy(vy)
        , vz(vz)
        , accx(accx)
        , accy(accy)
        , accz(accz)
        , yaw(yaw)
        , yaw_rate(yaw_rate)
    {}

    /**
     * @brief PositionTarget
     * @param that
     */
    PositionTarget(const PositionTarget & that)
        : Sensor(that)
        , coordinate_frame(that.coordinate_frame)
        , type_mask(that.type_mask)
        , x(that.x)
        , y(that.y)
        , z(that.z)
        , vx(that.vx)
        , vy(that.vy)
        , vz(that.vz)
        , accx(that.accx)
        , accy(that.accy)
        , accz(that.accz)
        , yaw(that.yaw)
        , yaw_rate(that.yaw_rate)
    {}

    /**
     * @brief clone
     * @param that
     */
    void clone(const PositionTarget & that) {
        Sensor::clone(that);

        coordinate_frame = that.coordinate_frame;
        type_mask = that.type_mask;
        x = that.x;
        y = that.y;
        z = that.z;
        vx = that.vx;
        vy = that.vy;
        vz = that.vz;
        accx = that.accx;
        accy = that.accy;
        accz = that.accz;
        yaw = that.yaw;
        yaw_rate = that.yaw_rate;
    }

    int coordinate_frame;
    int type_mask;
    double x;
    double y;
    double z;
    double vx;
    double vy;
    double vz;
    double accx;
    double accy;
    double accz;
    float yaw;
    float yaw_rate;

};
}
}
#endif
