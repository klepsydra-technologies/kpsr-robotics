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

#ifndef IMAGE_DATA_DDS_MAPPER_H
#define IMAGE_DATA_DDS_MAPPER_H

#include <streambuf>

#include <klepsydra/serialization/mapper.h>

#include <image_event_data.hpp>
#include <klepsydra/vision_ocv/image_event_data.h>

namespace kpsr {
template<>
/**
 * @brief The Mapper<kpsr::vision::ImageData, kpsr_dds_vision::ImageData> class
 *
 * @copyright 2023 Klepsydra Technologies AG
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
    void fromMiddleware(const kpsr_dds_vision_ocv::ImageData &message,
                        kpsr::vision_ocv::ImageData &event)
    {
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
    void toMiddleware(const kpsr::vision_ocv::ImageData &event,
                      kpsr_dds_vision_ocv::ImageData &message)
    {
        message.seq(event.seq);
        message.timestamp(event.timestamp);
        message.frameId(event.frameId);

        message.type(event.img.type());
        message.rows(event.img.rows);
        message.cols(event.img.cols);
        std::vector<unsigned char> data((unsigned char *) (event.img.data),
                                        (unsigned char *) event.img.data +
                                            event.img.elemSize() * event.img.total());
        message.data(data);
    }
};
} // namespace kpsr
#endif // IMAGE_DATA_DDS_MAPPER_H
