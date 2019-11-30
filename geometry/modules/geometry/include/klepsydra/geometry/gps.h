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
