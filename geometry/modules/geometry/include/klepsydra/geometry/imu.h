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

#ifndef KPSR_GEOMETRY_IMU_H_
#define KPSR_GEOMETRY_IMU_H_

// Include section.
#include "header.h"
#include "quaternion.h"
#include "vector3.h"
#include <array>
#include <klepsydra/core/sensor.h>

namespace kpsr {
namespace geometry {
// Klepsydra generated event class.
class Imu : public Sensor
{
public:
    // Default constructor.
    Imu() {}

    // Main constructor.
    Imu(const std::string &frameId,
        int seq,
        long timestamp,
        Quaternion orientation,
        std::array<double, 9> orientation_covariance,
        Vector3 angular_velocity,
        std::array<double, 9> angular_velocity_covariance,
        Vector3 linear_acceleration,
        std::array<double, 9> linear_acceleration_covariance)
        : Sensor(frameId, seq, timestamp)
        , orientation(orientation)
        , orientation_covariance(orientation_covariance)
        , angular_velocity(angular_velocity)
        , angular_velocity_covariance(angular_velocity_covariance)
        , linear_acceleration(linear_acceleration)
        , linear_acceleration_covariance(linear_acceleration_covariance)
    {}

    // Clone constructor. Needed by klepsydra core APIs.
    Imu(const Imu &that)
        : Sensor(that.frameId, that.seq, that.timestamp)
        , orientation(that.orientation)
        , orientation_covariance(that.orientation_covariance)
        , angular_velocity(that.angular_velocity)
        , angular_velocity_covariance(that.angular_velocity_covariance)
        , linear_acceleration(that.linear_acceleration)
        , linear_acceleration_covariance(that.linear_acceleration_covariance)
    {}

    // Clone method. Needed by klepsydra core APIs.
    void clone(const Imu &that)
    {
        Sensor::clone(that);
        this->orientation = that.orientation;
        this->orientation_covariance = that.orientation_covariance;
        this->angular_velocity = that.angular_velocity;
        this->angular_velocity_covariance = that.angular_velocity_covariance;
        this->linear_acceleration = that.linear_acceleration;
        this->linear_acceleration_covariance = that.linear_acceleration_covariance;
    }

    // List of fields.
    Quaternion orientation;
    std::array<double, 9> orientation_covariance;
    Vector3 angular_velocity;
    std::array<double, 9> angular_velocity_covariance;
    Vector3 linear_acceleration;
    std::array<double, 9> linear_acceleration_covariance;
};
} // namespace geometry
} // namespace kpsr
#endif
