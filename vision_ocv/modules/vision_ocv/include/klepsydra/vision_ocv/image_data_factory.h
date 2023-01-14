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

#ifndef IMAGE_DATA_FACTORY_H
#define IMAGE_DATA_FACTORY_H

#include <functional>
#include <memory>

#include <klepsydra/vision_ocv/image_event_data.h>

namespace kpsr {
namespace vision_ocv {
/**
 * @brief The ImageDataFactory class
 *
 * @copyright 2023 Klepsydra Technologies AG
 *
 * @version 2.0.1
 *
 * @ingroup kpsr-vision-composition
 *
 * @details This is a vision performance facility class that has several functions that can be used in conjuntion
 * with the disruptor and object pool classes. It handles the allocation of images, copy and resizing.
 */
class ImageDataFactory
{
public:
    /**
     * @brief ImageDataFactory
     * @param rows
     * @param cols
     * @param type
     * @param frameId
     */
    ImageDataFactory(int rows, int cols, int type, const std::string &frameId);

private:
    int _rows, _cols, _type;
    std::string _frameId;

public:
    /**
     * @brief creatorFunction
     * Function that creates new images based on the rows, cols and type members.
     */
    std::function<std::unique_ptr<kpsr::vision_ocv::ImageData>(void)> creatorFunction;

    /**
     * @brief initializerFunction
     * Resize of the image to meet the rows, cols and type member.
     */
    std::function<void(kpsr::vision_ocv::ImageData &)> initializerFunction;

    /**
     * @brief eventClonerFunction
     * Cloner function that does not perform any resizing.
     */
    std::function<void(const kpsr::vision_ocv::ImageData &, kpsr::vision_ocv::ImageData &)>
        eventClonerFunction;

protected:
    std::unique_ptr<kpsr::vision_ocv::ImageData> creator();

    void initializer(kpsr::vision_ocv::ImageData &imageEvent);

    void eventCloner(const kpsr::vision_ocv::ImageData &source, kpsr::vision_ocv::ImageData &target);
};
} // namespace vision_ocv
} // namespace kpsr
#endif // IMAGE_DATA_FACTORY_H
