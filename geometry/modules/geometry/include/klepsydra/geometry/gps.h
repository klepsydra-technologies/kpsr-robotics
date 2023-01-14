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

#ifndef KPSR_GEOMETRY_GPS_H_
#define KPSR_GEOMETRY_GPS_H_

// Include section.
#include "header.h"

namespace kpsr {
namespace geometry {
// Klepsydra generated event class.
class Gps
{
public:
    // Default constructor.
    Gps() {}

    // Main constructor.
    Gps(double latitude, double longitude, double altitude)
        : latitude(latitude)
        , longitude(longitude)
        , altitude(altitude)
    {}

    // Clone constructor. Needed by klepsydra core APIs.
    Gps(const Gps *that)
        : latitude(that->latitude)
        , longitude(that->longitude)
        , altitude(that->altitude)
    {}

    // Clone method. Needed by klepsydra core APIs.
    void clone(const Gps *that)
    {
        this->latitude = that->latitude;
        this->longitude = that->longitude;
        this->altitude = that->altitude;
    }

    // List of fields.
    double latitude;
    double longitude;
    double altitude;
};
} // namespace geometry
} // namespace kpsr
#endif
