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

#ifndef KPSR_GEOMETRY_IMU_H_
#define KPSR_GEOMETRY_IMU_H_


// Include section.
#include "header.h"
#include "vector3.h"
#include <array>
#include "quaternion.h"


namespace kpsr {
namespace geometry {
// Klepsydra generated event class.
class Imu {
public:
   // Default constructor.
   Imu() {}

   // Main constructor.
   Imu(
      Quaternion orientation,
      std::array<double,9> orientation_covariance,
      Vector3 angular_velocity,
      std::array<double,9> angular_velocity_covariance,
      Vector3 linear_acceleration,
      std::array<double,9> linear_acceleration_covariance)
      : orientation(orientation)
      , orientation_covariance(orientation_covariance)
      , angular_velocity(angular_velocity)
      , angular_velocity_covariance(angular_velocity_covariance)
      , linear_acceleration(linear_acceleration)
      , linear_acceleration_covariance(linear_acceleration_covariance)
   {}

   // Clone constructor. Needed by klepsydra core APIs.
   Imu(const Imu * that)
      : orientation(that->orientation)
      , orientation_covariance(that->orientation_covariance)
      , angular_velocity(that->angular_velocity)
      , angular_velocity_covariance(that->angular_velocity_covariance)
      , linear_acceleration(that->linear_acceleration)
      , linear_acceleration_covariance(that->linear_acceleration_covariance)
   {}

   // Clone method. Needed by klepsydra core APIs.
   void clone(const Imu * that) {
      this->orientation = that->orientation;
      this->orientation_covariance = that->orientation_covariance;
      this->angular_velocity = that->angular_velocity;
      this->angular_velocity_covariance = that->angular_velocity_covariance;
      this->linear_acceleration = that->linear_acceleration;
      this->linear_acceleration_covariance = that->linear_acceleration_covariance;
   }

   // List of fields.
   Quaternion orientation;
   std::array<double,9> orientation_covariance;
   Vector3 angular_velocity;
   std::array<double,9> angular_velocity_covariance;
   Vector3 linear_acceleration;
   std::array<double,9> linear_acceleration_covariance;
};
}
}
#endif
