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

#ifndef KPSR_GEOMETRY_QUATERNION_H_
#define KPSR_GEOMETRY_QUATERNION_H_


// Include section.


namespace kpsr {
namespace geometry {
// Klepsydra generated event class.
class Quaternion {
public:
   // Default constructor.
   Quaternion() {}

   // Main constructor.
   Quaternion(
      double x,
      double y,
      double z,
      double w)
      : x(x)
      , y(y)
      , z(z)
      , w(w)
   {}

   // Clone constructor. Needed by klepsydra core APIs.
   Quaternion(const Quaternion * that)
      : x(that->x)
      , y(that->y)
      , z(that->z)
      , w(that->w)
   {}

   // Clone method. Needed by klepsydra core APIs.
   void clone(const Quaternion * that) {
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
}
}
#endif
