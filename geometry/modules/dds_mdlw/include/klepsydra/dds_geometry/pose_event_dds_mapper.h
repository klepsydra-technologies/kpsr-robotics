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

#ifndef POSE_EVENT_DATA_DDS_MAPPER_H
#define POSE_EVENT_DATA_DDS_MAPPER_H

#include <pose_event.hpp>

#include <klepsydra/serialization/mapper.h>

#include <klepsydra/geometry/pose_event_data.h>

namespace kpsr {
template<>
/**
 * @brief The Mapper<kpsr::geometry::PoseEventData, kpsr_dds_geometry::PoseEventData> class
 *
 * @copyright Klepsydra Technologies 2019-2020.
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-geometry-dds-composition
 *
 * @details Geometry object mapper for DDS middleware
 */
class Mapper<kpsr::geometry::PoseEventData, kpsr_dds_geometry::PoseEventData>
{
public:

    /**
     * @brief fromMiddleware
     * @param message
     * @param event
     */
    void fromMiddleware(const kpsr_dds_geometry::PoseEventData & message, kpsr::geometry::PoseEventData& event) {
        event.frameId = message.frameId();
        event.seq = message.seq();
        event.timestamp = message.timestamp();

        event.eulerAvailable = message.eulerAvailable();
        event.posCovarianceAvailable = message.posCovarianceAvailable();

        event.x = message.x();
        event.y = message.y();
        event.z = message.z();

        event.roll = message.roll();
        event.pitch = message.pitch();
        event.yaw = message.yaw();

        event.qx = message.qx();
        event.qy = message.qy();
        event.qz = message.qz();
        event.qw = message.qw();

        event.positionCovariance.resize(message.positionCovariance().size());
        std::transform(message.positionCovariance().begin(), message.positionCovariance().end(), event.positionCovariance.begin(),
                       [](const double eventItem) {
            return eventItem;
        });
    }

    /**
     * @brief toMiddleware
     * @param event
     * @param message
     */
    void toMiddleware(const kpsr::geometry::PoseEventData & event, kpsr_dds_geometry::PoseEventData& message) {
        message.seq(event.seq);
        message.timestamp(event.timestamp);
        message.frameId(event.frameId);

        message.eulerAvailable(event.eulerAvailable);
        message.posCovarianceAvailable(event.posCovarianceAvailable);

        message.x(event.x);
        message.y(event.y);
        message.z(event.z);

        message.roll(event.roll);
        message.pitch(event.pitch);
        message.yaw(event.yaw);

        message.qx(event.qx);
        message.qy(event.qy);
        message.qz(event.qz);
        message.qw(event.qw);

        message.positionCovariance().resize(event.positionCovariance.size());
        std::transform(event.positionCovariance.begin(), event.positionCovariance.end(), message.positionCovariance().begin(),
                       [&](double eventData) {
            return eventData;
        });
    }
};
}
#endif // POSE_EVENT_DATA_DDS_MAPPER_H
