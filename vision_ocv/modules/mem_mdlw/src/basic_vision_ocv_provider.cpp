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

#include <klepsydra/mem_vision_ocv/basic_vision_ocv_provider.h>

kpsr::vision_ocv::mem::BasicVisionMiddlewareProvider::BasicVisionMiddlewareProvider(Container * container,
                                                                                    int rows,
                                                                                    int cols,
                                                                                    int type,
                                                                                    std::string frameId,
                                                                                    std::string eventName,
                                                                                    int queueSize,
                                                                                    int poolSize,
                                                                                    bool discardItemsWhenFull)
    : _imageDataFactory(new kpsr::vision_ocv::ImageDataFactory(rows, cols, type, frameId))
    , underlying(new kpsr::mem::BasicMiddlewareProvider<kpsr::vision_ocv::ImageData>
                 (container, eventName, queueSize, poolSize,
                  _imageDataFactory->initializerFunction,
                  _imageDataFactory->eventClonerFunction,
                  discardItemsWhenFull))
{}
