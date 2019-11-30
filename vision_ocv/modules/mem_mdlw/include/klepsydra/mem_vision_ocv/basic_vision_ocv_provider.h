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
