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
