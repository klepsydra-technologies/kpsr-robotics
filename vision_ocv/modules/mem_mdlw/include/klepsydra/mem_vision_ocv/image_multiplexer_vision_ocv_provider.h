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
