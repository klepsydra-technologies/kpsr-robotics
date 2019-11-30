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
