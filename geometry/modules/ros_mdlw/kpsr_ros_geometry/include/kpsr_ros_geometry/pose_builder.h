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

#ifndef POSE_BUILDER_H
#define POSE_BUILDER_H

#include <klepsydra/core/environment.h>
#include <klepsydra/geometry/pose_event_data.h>

namespace kpsr
{
namespace geometry
{
namespace ros_mdlw
{
/**
 * @brief The PoseBuilder class
 *
 * @copyright Klepsydra Technologies 2019-2020.
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
    static void createPoseEvent(const char * frameId, double x, double y, double z,
                                double qx, double qy, double qz, double qw,
                                double * covariance, bool calculateEuler,
                                PoseEventData & poseEventData);

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
    static void createPoseEvent(const char * frameId, float x, float y, float z,
                                float qx, float qy, float qz, float qw,
                                float * covariance, bool calculateEuler,
                                PoseEventData & poseEventData);
};
}
}
}
#endif
