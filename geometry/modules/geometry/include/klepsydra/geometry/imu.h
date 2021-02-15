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

#ifndef KPSR_GEOMETRY_IMU_H_
#define KPSR_GEOMETRY_IMU_H_


// Include section.
#include "header.h"
#include "vector3.h"
#include <array>
#include "quaternion.h"
#include <klepsydra/core/sensor.h>


namespace kpsr {
namespace geometry {
// Klepsydra generated event class.
class Imu : public Sensor {
public:
   // Default constructor.
   Imu() {}

   // Main constructor.
   Imu(
      std::string frameId,
      int seq,
      long timestamp,
      Quaternion orientation,
      std::array<double,9> orientation_covariance,
      Vector3 angular_velocity,
      std::array<double,9> angular_velocity_covariance,
      Vector3 linear_acceleration,
      std::array<double,9> linear_acceleration_covariance)
      : Sensor(frameId, seq, timestamp)
      , orientation(orientation)
      , orientation_covariance(orientation_covariance)
      , angular_velocity(angular_velocity)
      , angular_velocity_covariance(angular_velocity_covariance)
      , linear_acceleration(linear_acceleration)
      , linear_acceleration_covariance(linear_acceleration_covariance)
   {}

   // Clone constructor. Needed by klepsydra core APIs.
   Imu(const Imu & that)
      : Sensor(that.frameId, that.seq, that.timestamp)
      , orientation(that.orientation)
      , orientation_covariance(that.orientation_covariance)
      , angular_velocity(that.angular_velocity)
      , angular_velocity_covariance(that.angular_velocity_covariance)
      , linear_acceleration(that.linear_acceleration)
      , linear_acceleration_covariance(that.linear_acceleration_covariance)
   {}

   // Clone method. Needed by klepsydra core APIs.
   void clone(const Imu & that) {
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
   std::array<double,9> orientation_covariance;
   Vector3 angular_velocity;
   std::array<double,9> angular_velocity_covariance;
   Vector3 linear_acceleration;
   std::array<double,9> linear_acceleration_covariance;
};
}
}
#endif
