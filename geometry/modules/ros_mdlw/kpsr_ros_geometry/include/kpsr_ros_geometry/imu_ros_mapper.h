/*
 * Copyright 2023 Klepsydra Technologies AG
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef IMU_ROS_MAPPER_H
#define IMU_ROS_MAPPER_H

#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/Vector3.h"
#include "kpsr_ros_geometry/header_ros_mapper.h"
#include "kpsr_ros_geometry/quaternion_ros_mapper.h"
#include "kpsr_ros_geometry/vector3_ros_mapper.h"
#include "sensor_msgs/Imu.h"
#include "std_msgs/Header.h"
#include <algorithm>
#include <array>

#include <klepsydra/geometry/imu.h>
#include <klepsydra/serialization/mapper.h>

namespace kpsr {
template<>
/**
 * @brief The Mapper<kpsr::geometry::Imu, sensor_msgs::Imu> class
 *
 * @copyright 2023 Klepsydra Technologies AG
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-geometry-ros-composition
 *
 * @details Geometry object mapper for ROS middleware.
 */
class Mapper<kpsr::geometry::Imu, sensor_msgs::Imu>
{
public:
    void fromMiddleware(const sensor_msgs::Imu &message, kpsr::geometry::Imu &event)
    {
        event.frameId = message.header.frame_id;
        event.seq = message.header.seq;
        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch());
        event.timestamp = ms.count();

        QuaternionMapper.fromMiddleware(message.orientation, event.orientation);
        std::transform(message.orientation_covariance.begin(),
                       message.orientation_covariance.end(),
                       event.orientation_covariance.begin(),
                       [](double data) -> double { return data; });
        Vector3Mapper.fromMiddleware(message.angular_velocity, event.angular_velocity);
        std::transform(message.angular_velocity_covariance.begin(),
                       message.angular_velocity_covariance.end(),
                       event.angular_velocity_covariance.begin(),
                       [](double data) -> double { return data; });
        Vector3Mapper.fromMiddleware(message.linear_acceleration, event.linear_acceleration);
        std::transform(message.linear_acceleration_covariance.begin(),
                       message.linear_acceleration_covariance.end(),
                       event.linear_acceleration_covariance.begin(),
                       [](double data) -> double { return data; });
    }

    void toMiddleware(const kpsr::geometry::Imu &event, sensor_msgs::Imu &message)
    {
        std_msgs::Header header;
        header.seq = event.seq;
        header.stamp = ros::Time::now();
        header.frame_id = event.frameId;

        message.header = header;

        QuaternionMapper.toMiddleware(event.orientation, message.orientation);
        std::transform(event.linear_acceleration_covariance.begin(),
                       event.linear_acceleration_covariance.end(),
                       message.linear_acceleration_covariance.begin(),
                       [](double data) -> double { return data; });
        Vector3Mapper.toMiddleware(event.angular_velocity, message.angular_velocity);
        std::transform(event.linear_acceleration_covariance.begin(),
                       event.linear_acceleration_covariance.end(),
                       message.linear_acceleration_covariance.begin(),
                       [](double data) -> double { return data; });
        Vector3Mapper.toMiddleware(event.linear_acceleration, message.linear_acceleration);
        std::transform(event.linear_acceleration_covariance.begin(),
                       event.linear_acceleration_covariance.end(),
                       message.linear_acceleration_covariance.begin(),
                       [](double data) -> double { return data; });
    }

    // Related mapper instance for kpsr::geometry::Quaternion
    Mapper<kpsr::geometry::Quaternion, geometry_msgs::Quaternion> QuaternionMapper;

    // Related mapper instance for kpsr::geometry::Vector3
    Mapper<kpsr::geometry::Vector3, geometry_msgs::Vector3> Vector3Mapper;
};
} // namespace kpsr
#endif
