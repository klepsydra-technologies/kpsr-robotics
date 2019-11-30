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
