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

#ifndef IMU_ROS_MAPPER_H
#define IMU_ROS_MAPPER_H

#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/Vector3.h"
#include "kpsr_ros_geometry/header_ros_mapper.h"
#include "kpsr_ros_geometry/quaternion_ros_mapper.h"
#include "sensor_msgs/Imu.h"
#include "std_msgs/Header.h"
#include "kpsr_ros_geometry/vector3_ros_mapper.h"
#include <algorithm>
#include <array>

#include <klepsydra/geometry/imu.h>
#include <klepsydra/serialization/mapper.h>

namespace kpsr {
template <>
/**
 * @brief The Mapper<kpsr::geometry::Imu, sensor_msgs::Imu> class
 *
 * @copyright Klepsydra Technologies 2019-2020.
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-geometry-ros-composition
 *
 * @details Geometry object mapper for ROS middleware.
 */
class Mapper<kpsr::geometry::Imu, sensor_msgs::Imu> {
public:
  void fromMiddleware(const sensor_msgs::Imu &message,
                      kpsr::geometry::Imu &event) {
    QuaternionMapper.fromMiddleware( message.orientation,
                                    event.orientation);
    std::transform(message.orientation_covariance.begin(),
                   message.orientation_covariance.end(),
                   event.orientation_covariance.begin(),
                   [](double data) -> double { return data; });
    Vector3Mapper.fromMiddleware( message.angular_velocity,
                                 event.angular_velocity);
    std::transform(message.angular_velocity_covariance.begin(),
                   message.angular_velocity_covariance.end(),
                   event.angular_velocity_covariance.begin(),
                   [](double data) -> double { return data; });
    Vector3Mapper.fromMiddleware( message.linear_acceleration,
                                 event.linear_acceleration);
    std::transform(message.linear_acceleration_covariance.begin(),
                   message.linear_acceleration_covariance.end(),
                   event.linear_acceleration_covariance.begin(),
                   [](double data) -> double { return data; });
  }

  void toMiddleware(const kpsr::geometry::Imu &event,
                    sensor_msgs::Imu &message) {
    QuaternionMapper.toMiddleware( event.orientation,
                                                message.orientation);
    std::transform(event.linear_acceleration_covariance.begin(),
                   event.linear_acceleration_covariance.end(),
                   message.linear_acceleration_covariance.begin(),
                   [](double data) -> double { return data; });
    Vector3Mapper.toMiddleware( event.angular_velocity, message.angular_velocity);
    std::transform(event.linear_acceleration_covariance.begin(),
                   event.linear_acceleration_covariance.end(),
                   message.linear_acceleration_covariance.begin(),
                   [](double data) -> double { return data; });
    Vector3Mapper.toMiddleware( event.linear_acceleration, message.linear_acceleration);
    std::transform(event.linear_acceleration_covariance.begin(),
                   event.linear_acceleration_covariance.end(),
                   message.linear_acceleration_covariance.begin(),
                   [](double data) -> double { return data; });
  }

  // Related mapper instance for kpsr::geometry::Header
  Mapper<kpsr::geometry::Header, std_msgs::Header> HeaderMapper;

  // Related mapper instance for kpsr::geometry::Quaternion
  Mapper<kpsr::geometry::Quaternion, geometry_msgs::Quaternion>
      QuaternionMapper;

  // Related mapper instance for kpsr::geometry::Vector3
  Mapper<kpsr::geometry::Vector3, geometry_msgs::Vector3> Vector3Mapper;
};
}
#endif
