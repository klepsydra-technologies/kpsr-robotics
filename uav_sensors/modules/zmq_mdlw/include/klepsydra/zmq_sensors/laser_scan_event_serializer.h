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

#ifndef LASER_SCAN_EVENT_ZMQ_SERIALIZER_H
#define LASER_SCAN_EVENT_ZMQ_SERIALIZER_H

#include <cereal/cereal.hpp>

#include <cereal/types/vector.hpp>

#include <klepsydra/sensors/laser_scan_event.h>

namespace cereal {
template<class Archive>
void serialize(Archive & archive, kpsr::sensors::LaserScanEvent & event)
{
    archive(CEREAL_NVP(event.frameId),
            CEREAL_NVP(event.seq),
            CEREAL_NVP(event.timestamp),
            CEREAL_NVP(event.angle_min),
            CEREAL_NVP(event.angle_max),
            CEREAL_NVP(event.angle_increment),
            CEREAL_NVP(event.time_increment),
            CEREAL_NVP(event.scan_time),
            CEREAL_NVP(event.range_min),
            CEREAL_NVP(event.range_max),
            CEREAL_NVP(event.ranges),
            CEREAL_NVP(event.intensities));
}
}
#endif // LASER_SCAN_EVENT_ZMQ_SERIALIZER_H
