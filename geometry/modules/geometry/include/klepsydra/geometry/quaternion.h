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

#ifndef KPSR_GEOMETRY_QUATERNION_H_
#define KPSR_GEOMETRY_QUATERNION_H_

// Include section.

namespace kpsr {
namespace geometry {
// Klepsydra generated event class.
class Quaternion
{
public:
    // Default constructor.
    Quaternion() {}

    // Main constructor.
    Quaternion(double x, double y, double z, double w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {}

    // Clone constructor. Needed by klepsydra core APIs.
    Quaternion(const Quaternion *that)
        : x(that->x)
        , y(that->y)
        , z(that->z)
        , w(that->w)
    {}

    // Clone method. Needed by klepsydra core APIs.
    void clone(const Quaternion *that)
    {
        this->x = that->x;
        this->y = that->y;
        this->z = that->z;
        this->w = that->w;
    }

    // List of fields.
    double x;
    double y;
    double z;
    double w;
};
} // namespace geometry
} // namespace kpsr
#endif
