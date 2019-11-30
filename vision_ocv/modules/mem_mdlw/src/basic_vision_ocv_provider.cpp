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
