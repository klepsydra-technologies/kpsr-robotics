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

#ifndef KPSR_GEOMETRY_VECTOR3_H_
#define KPSR_GEOMETRY_VECTOR3_H_

namespace kpsr {
namespace geometry {
// Klepsydra generated event class.
class Vector3
{
public:
    // Default constructor.
    Vector3() {}

    // Main constructor.
    Vector3(double x, double y, double z)
        : x(x)
        , y(y)
        , z(z)
    {}

    // Clone constructor. Needed by klepsydra core APIs.
    Vector3(const Vector3 *that)
        : x(that->x)
        , y(that->y)
        , z(that->z)
    {}

    // Clone method. Needed by klepsydra core APIs.
    void clone(const Vector3 *that)
    {
        this->x = that->x;
        this->y = that->y;
        this->z = that->z;
    }

    // List of fields.
    double x;
    double y;
    double z;
};
} // namespace geometry
} // namespace kpsr
#endif
