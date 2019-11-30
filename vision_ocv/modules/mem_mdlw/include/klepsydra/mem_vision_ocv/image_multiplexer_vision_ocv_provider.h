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

#ifndef VISION_HIGH_PERFORMANCE_PROVIDER_H
#define VISION_HIGH_PERFORMANCE_PROVIDER_H

#include <cassert>
#include <functional>

#include <klepsydra/high_performance/data_multiplexer_middleware_provider.h>

#include <klepsydra/vision_ocv/image_event_data.h>
#include <klepsydra/vision_ocv/image_data_factory.h>

namespace kpsr {
namespace vision_ocv {
namespace high_performance {
template <std::size_t BufferSize>
/**
 * @brief The ImageMultiplexerVisionMiddlewareProvider class
 *
 * @copyright Klepsydra Technologies 2019-2020.
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-vision-high_performance-composition
 *
 * @details A syntactic sugar provider for mixing the high_performance provider with the image factory class.
 *
 */
class ImageMultiplexerVisionMiddlewareProvider {
public:
    /**
     * @brief ImageMultiplexerVisionMiddlewareProvider
     * @param container
     * @param name
     * @param rows
     * @param cols
     * @param type
     * @param frameId
     */
    ImageMultiplexerVisionMiddlewareProvider(Container * container, std::string name, int rows, int cols, int type, std::string frameId)
        : imageDataFactory(rows, cols, type, frameId)
        , underlying(new kpsr::high_performance::DataMultiplexerMiddlewareProvider<kpsr::vision_ocv::ImageData, BufferSize>
          (container, name, imageDataFactory.initializerFunction, imageDataFactory.eventClonerFunction))
    {}

    /**
     * @brief imageDataFactory
     */
    kpsr::vision_ocv::ImageDataFactory imageDataFactory;

    /**
     * @brief _high_performanceProvider
     */
    kpsr::high_performance::DataMultiplexerMiddlewareProvider<kpsr::vision_ocv::ImageData, BufferSize> * underlying;
};
}
}
}

#endif // VISION_HIGH_PERFORMANCE_PROVIDER_H
