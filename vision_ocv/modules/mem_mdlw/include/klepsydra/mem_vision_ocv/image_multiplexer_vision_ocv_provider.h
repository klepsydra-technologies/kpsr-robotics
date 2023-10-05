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

#ifndef VISION_HIGH_PERFORMANCE_PROVIDER_H
#define VISION_HIGH_PERFORMANCE_PROVIDER_H

#include <cassert>
#include <functional>

#include <klepsydra/high_performance/data_multiplexer_middleware_provider.h>

#include <klepsydra/vision_ocv/image_data_factory.h>
#include <klepsydra/vision_ocv/image_event_data.h>

namespace kpsr {
namespace vision_ocv {
namespace high_performance {
template<std::size_t BufferSize>
/**
 * @brief The ImageMultiplexerVisionMiddlewareProvider class
 *
 * @copyright 2023 Klepsydra Technologies AG
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-vision-high_performance-composition
 *
 * @details A syntactic sugar provider for mixing the high_performance provider with the image factory class.
 *
 */
class ImageMultiplexerVisionMiddlewareProvider
{
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
    ImageMultiplexerVisionMiddlewareProvider(Container *container,
                                             const std::string &name,
                                             int rows,
                                             int cols,
                                             int type,
                                             const std::string &frameId)
        : imageDataFactory(rows, cols, type, frameId)
        , underlying(new kpsr::high_performance::DataMultiplexerMiddlewareProvider<
                     kpsr::vision_ocv::ImageData,
                     BufferSize>(container,
                                 name,
                                 imageDataFactory.initializerFunction,
                                 imageDataFactory.eventClonerFunction))
    {}

    /**
     * @brief imageDataFactory
     */
    kpsr::vision_ocv::ImageDataFactory imageDataFactory;

    /**
     * @brief _high_performanceProvider
     */
    using HighPerformanceImageDataPovider =
        kpsr::high_performance::DataMultiplexerMiddlewareProvider<kpsr::vision_ocv::ImageData,
                                                                  BufferSize>;
    std::unique_ptr<HighPerformanceImageDataPovider> underlying;
};
} // namespace high_performance
} // namespace vision_ocv
} // namespace kpsr

#endif // VISION_HIGH_PERFORMANCE_PROVIDER_H
