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
