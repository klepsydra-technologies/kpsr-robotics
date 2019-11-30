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

#ifndef KPSR_GEOMETRY_HEADER_H_
#define KPSR_GEOMETRY_HEADER_H_


// Include section.
#include <string>


namespace kpsr {
namespace geometry {
// Klepsydra generated event class.
class Header {
public:
   // Default constructor.
   Header() {}

   // Main constructor.
   Header(
      unsigned int seq,
      std::string frame_id)
      : seq(seq)
      , frame_id(frame_id)
   {}

   // Clone constructor. Needed by klepsydra core APIs.
   Header(const Header * that)
      : seq(that->seq)
      , frame_id(that->frame_id)
   {}

   // Clone method. Needed by klepsydra core APIs.
   void clone(const Header * that) {
      this->seq = that->seq;
      this->frame_id = that->frame_id;
   }

   // List of fields.
   unsigned int seq;
   std::string frame_id;
};
}
}
#endif
