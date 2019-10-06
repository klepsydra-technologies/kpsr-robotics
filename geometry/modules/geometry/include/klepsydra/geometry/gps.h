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

#ifndef KPSR_GEOMETRY_GPS_H_
#define KPSR_GEOMETRY_GPS_H_

// Include section.
#include "header.h"

namespace kpsr {
namespace geometry {
// Klepsydra generated event class.
class Gps {
public:
  // Default constructor.
  Gps() {}

  // Main constructor.
  Gps(double latitude, double longitude, double altitude)
      : latitude(latitude), longitude(longitude), altitude(altitude) {}

  // Clone constructor. Needed by klepsydra core APIs.
  Gps(const Gps *that)
      : latitude(that->latitude), longitude(that->longitude),
        altitude(that->altitude) {}

  // Clone method. Needed by klepsydra core APIs.
  void clone(const Gps *that) {
    this->latitude = that->latitude;
    this->longitude = that->longitude;
    this->altitude = that->altitude;
  }

  // List of fields.
  double latitude;
  double longitude;
  double altitude;
};
}
}
#endif
