// Copyright 2023 Klepsydra Technologies AG
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <klepsydra/mem_vision_ocv/basic_vision_ocv_provider.h>

kpsr::vision_ocv::mem::BasicVisionMiddlewareProvider::BasicVisionMiddlewareProvider(
    Container *container,
    int rows,
    int cols,
    int type,
    const std::string &frameId,
    const std::string &eventName,
    int queueSize,
    int poolSize,
    bool discardItemsWhenFull)
    : _imageDataFactory(new kpsr::vision_ocv::ImageDataFactory(rows, cols, type, frameId))
    , underlying(new kpsr::mem::BasicMiddlewareProvider<kpsr::vision_ocv::ImageData>(
          container,
          eventName,
          queueSize,
          poolSize,
          _imageDataFactory->initializerFunction,
          _imageDataFactory->eventClonerFunction,
          discardItemsWhenFull))
{}
