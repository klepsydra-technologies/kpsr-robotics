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

#include <klepsydra/core/event_emitter_middleware_provider.h>

#include <klepsydra/vision_ocv/file_image_stream_service.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "gtest/gtest.h"

#include "config.h"

#include <klepsydra/vision_ocv/mpeg_writer.h>

TEST(VideoStreamingTest, BasicStreamingTest) {

    kpsr::EventEmitterMiddlewareProvider<kpsr::vision_ocv::ImageData> imageEventEmitter(nullptr, "image_provider", 0, nullptr, nullptr);
    kpsr::EventEmitterMiddlewareProvider<std::vector<uchar>> encodedImageEventEmitter(nullptr, "encoded_image_provider", 0, nullptr, nullptr);

    kpsr::vision_ocv::FileImageStreamingService writeService(nullptr, imageEventEmitter.getPublisher(), TEST_DATA, true);

    kpsr::vision_ocv::MJPEGWriter streamingService(8080, 180000, 95,
                                                   imageEventEmitter.getSubscriber(),
                                                   encodedImageEventEmitter.getPublisher(),
                                                   encodedImageEventEmitter.getSubscriber());

    writeService.start();
    streamingService.start();

    // Publish some integers.
    for (int i = 0; i < 50; i++) {
        //spdlog::info("Executing services.");
        writeService.execute();
        usleep(1000000);
    }

    streamingService.stop();
    writeService.stop();
}

