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

#ifndef KPSR_GEOMETRY_VECTOR3_H_
#define KPSR_GEOMETRY_VECTOR3_H_

namespace kpsr {
namespace geometry {
// Klepsydra generated event class.
class Vector3 {
public:
   // Default constructor.
   Vector3() {}

   // Main constructor.
   Vector3(
      double x,
      double y,
      double z)
      : x(x)
      , y(y)
      , z(z)
   {}

   // Clone constructor. Needed by klepsydra core APIs.
   Vector3(const Vector3 * that)
      : x(that->x)
      , y(that->y)
      , z(that->z)
   {}

   // Clone method. Needed by klepsydra core APIs.
   void clone(const Vector3 * that) {
      this->x = that->x;
      this->y = that->y;
      this->z = that->z;
   }

   // List of fields.
   double x;
   double y;
   double z;
};
}
}
#endif
