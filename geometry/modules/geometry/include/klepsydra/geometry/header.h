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
