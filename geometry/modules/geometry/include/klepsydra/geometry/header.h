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

#ifndef KPSR_GEOMETRY_HEADER_H_
#define KPSR_GEOMETRY_HEADER_H_

// Include section.
#include <string>

namespace kpsr {
namespace geometry {
// Klepsydra generated event class.
class Header
{
public:
    // Default constructor.
    Header() {}

    // Main constructor.
    Header(unsigned int seq, const std::string &frame_id)
        : seq(seq)
        , frame_id(frame_id)
    {}

    // Clone constructor. Needed by klepsydra core APIs.
    Header(const Header *that)
        : seq(that->seq)
        , frame_id(that->frame_id)
    {}

    // Clone method. Needed by klepsydra core APIs.
    void clone(const Header *that)
    {
        this->seq = that->seq;
        this->frame_id = that->frame_id;
    }

    // List of fields.
    unsigned int seq;
    std::string frame_id;
};
} // namespace geometry
} // namespace kpsr
#endif
