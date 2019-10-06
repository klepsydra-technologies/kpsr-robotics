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

#ifndef IMAGE_DATA_DDS_MAPPER_H
#define IMAGE_DATA_DDS_MAPPER_H

#include <streambuf>

#include <klepsydra/serialization/mapper.h>

#include <klepsydra/vision_ocv/image_event_data.h>
#include <image_event_data.hpp>

namespace kpsr {
template<>
/**
 * @brief The Mapper<kpsr::vision::ImageData, kpsr_dds_vision::ImageData> class
 *
 * @copyright Klepsydra Technologies 2019-2020.
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-vision-ddsstg-composition
 *
 */
class Mapper<kpsr::vision_ocv::ImageData, kpsr_dds_vision_ocv::ImageData>
{
public:

    /**
    * @brief fromMiddleware
    * @param message
    * @param event
    */
    void fromMiddleware(const kpsr_dds_vision_ocv::ImageData & message, kpsr::vision_ocv::ImageData& event) {
        event.frameId = message.frameId();
        event.seq = message.seq();
        event.timestamp = message.timestamp();

        event.img.create(message.rows(), message.cols(), message.type());
        std::copy(message.data().begin(), message.data().end(), event.img.data);
    }

    /**
    * @brief toMiddleware
    * @param event
    * @param message
    */
    void toMiddleware(const kpsr::vision_ocv::ImageData & event, kpsr_dds_vision_ocv::ImageData& message) {
        message.seq(event.seq);
        message.timestamp(event.timestamp);
        message.frameId(event.frameId);

        message.type(event.img.type());
        message.rows(event.img.rows);
        message.cols(event.img.cols);
        std::vector<unsigned char> data((unsigned char*)(event.img.data), (unsigned char*)event.img.data + event.img.elemSize() * event.img.total());
        message.data(data);
    }
};
}
#endif // IMAGE_DATA_DDS_MAPPER_H
