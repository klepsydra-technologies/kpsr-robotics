/**
 *                               Klepsydra Toolset
 *
 *   This software and documentation are Copyright 2016 to 2017 Klepsydra Robotics
 *   Limited and its licensees. All rights reserved. See file:
 *
 *                               LICENSE.md
 *
 *   for full copyright notice and license terms.
 *
 */

#ifndef IMAGE_DATA_FACTORY_H
#define IMAGE_DATA_FACTORY_H

#include <memory>
#include <functional>

#include <klepsydra/vision_ocv/image_event_data.h>

namespace kpsr {
namespace vision_ocv {
/**
 * @brief The ImageDataFactory class
 *
 * @copyright Klepsydra Robotics 2017-2018.
 *
 * @version 2.0.1
 *
 * @ingroup kpsr-vision-composition
 *
 * @details This is a vision performance facility class that has several functions that can be used in conjuntion
 * with the disruptor and object pool classes. It handles the allocation of images, copy and resizing.
 */
class ImageDataFactory {
public:
    /**
     * @brief ImageDataFactory
     * @param rows
     * @param cols
     * @param type
     * @param frameId
     */
    ImageDataFactory(int rows, int cols, int type, std::string frameId);

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
    std::function<void(const kpsr::vision_ocv::ImageData &, kpsr::vision_ocv::ImageData &)> eventClonerFunction;

protected:
    std::unique_ptr<kpsr::vision_ocv::ImageData> creator();

    void initializer(kpsr::vision_ocv::ImageData & imageEvent);

    void eventCloner(const kpsr::vision_ocv::ImageData & source, kpsr::vision_ocv::ImageData & target);

};
}
}
#endif // IMAGE_DATA_FACTORY_H
