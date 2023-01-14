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

#ifndef VISION_BASIC_MIDDLEWARE_PROVIDER_H
#define VISION_BASIC_MIDDLEWARE_PROVIDER_H

#include <klepsydra/mem_core/basic_middleware_provider.h>

#include <klepsydra/vision_ocv/image_data_factory.h>
#include <klepsydra/vision_ocv/image_event_data.h>

namespace kpsr {
namespace vision_ocv {
namespace mem {
/**
 * @brief The BasicVisionMiddlewareProvider class
 *
 * @copyright 2023 Klepsydra Technologies AG
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
class BasicVisionMiddlewareProvider
{
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
    BasicVisionMiddlewareProvider(Container *container,
                                  int rows,
                                  int cols,
                                  int type,
                                  const std::string &frameId,
                                  const std::string &eventName,
                                  int queueSize,
                                  int poolSize,
                                  bool discardItemsWhenFull);

    /**
     * @brief _imageDataFactory
     */
    kpsr::vision_ocv::ImageDataFactory *_imageDataFactory;

    /**
     * @brief underlying
     */
    kpsr::mem::BasicMiddlewareProvider<kpsr::vision_ocv::ImageData> *underlying;
};
} // namespace mem
} // namespace vision_ocv
} // namespace kpsr

#endif // VISION_BASIC_MIDDLEWARE_PROVIDER_H
