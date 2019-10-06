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

#ifndef VISION_BASIC_MIDDLEWARE_PROVIDER_H
#define VISION_BASIC_MIDDLEWARE_PROVIDER_H

#include <klepsydra/mem_core/basic_middleware_provider.h>

#include <klepsydra/vision_ocv/image_event_data.h>
#include <klepsydra/vision_ocv/image_data_factory.h>

namespace kpsr {
namespace vision_ocv {
namespace mem {
/**
 * @brief The BasicVisionMiddlewareProvider class
 *
 * @copyright Klepsydra Technologies 2019-2020.
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-vision-composition
 *
 * @details A safe queue provider wrapper that adds the vision factory performance tool. Its use is very simple as
 * the following example shows:
@code
    //Create provider and start it;
    kpsr::vision_ocv::BasicVisionMiddlewareProvider provider(nullptr, 1080, 2040, 16, "body", "raw_image", 4, 6, false);
    provider.underlying->start();

    //Create a publisher;
    kpsr::Publisher<kpsr::vision_ocv::ImageData> * publisher = provider.underlying->getPublisher();

    //Create a subscriber;
    kpsr::Subscriber<kpsr::vision_ocv::ImageData> * subscriber = provider.underlying->getSubscriber();
@endcode
 *
 */
class BasicVisionMiddlewareProvider {
public:
    /**
     * @brief BasicVisionMiddlewareProvider
     * @param container
     * @param rows
     * @param cols
     * @param type
     * @param frameId
     * @param eventName
     * @param queueSize
     * @param poolSize
     * @param discardItemsWhenFull
     */
    BasicVisionMiddlewareProvider(Container * container, int rows, int cols, int type, std::string frameId,
                                  std::string eventName,
                                  int queueSize,
                                  int poolSize,
                                  bool discardItemsWhenFull);

    /**
     * @brief _imageDataFactory
     */
    kpsr::vision_ocv::ImageDataFactory * _imageDataFactory;

    /**
     * @brief underlying
     */
    kpsr::mem::BasicMiddlewareProvider<kpsr::vision_ocv::ImageData> * underlying;

};
}
}
}

#endif // VISION_BASIC_MIDDLEWARE_PROVIDER_H
