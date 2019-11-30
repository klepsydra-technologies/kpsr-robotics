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

#ifndef POSE_EVENT_DATA_ZMQ_SERIALIZER_H
#define POSE_EVENT_DATA_ZMQ_SERIALIZER_H

#include <cereal/cereal.hpp>

#include <cereal/types/vector.hpp>

#include <klepsydra/geometry/pose_event_data.h>

namespace cereal {
template<class Archive>
void serialize(Archive & archive, kpsr::geometry::PoseEventData & event)
{
    archive(CEREAL_NVP(event.frameId),
            CEREAL_NVP(event.seq),
            CEREAL_NVP(event.timestamp),
            CEREAL_NVP(event.eulerAvailable),
            CEREAL_NVP(event.posCovarianceAvailable),
            CEREAL_NVP(event.x),
            CEREAL_NVP(event.y),
            CEREAL_NVP(event.z),
            CEREAL_NVP(event.roll),
            CEREAL_NVP(event.pitch),
            CEREAL_NVP(event.yaw),
            CEREAL_NVP(event.positionCovariance),
            CEREAL_NVP(event.qx),
            CEREAL_NVP(event.qy),
            CEREAL_NVP(event.qz),
            CEREAL_NVP(event.qw));
}
}
#endif // POSE_EVENT_DATA_ZMQ_SERIALIZER_H
