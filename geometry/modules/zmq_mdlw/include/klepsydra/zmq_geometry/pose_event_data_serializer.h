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
