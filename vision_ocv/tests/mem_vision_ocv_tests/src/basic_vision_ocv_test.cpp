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

#include <klepsydra/vision_ocv/file_image_stream_service.h>

#include "simple_read_service.h"
#include "slow_read_service.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

#include "gtest/gtest.h"

#include "config.h"

TEST(BasicVisionTest, BasicVisionTest) {
    kpsr::vision_ocv::mem::BasicVisionMiddlewareProvider provider(nullptr, 1080, 2040, 16, "body", "raw_image", 4, 6, false);
    provider.underlying->start();

    //spdlog::info("Creating services.");
    kpsr::Publisher<kpsr::vision_ocv::ImageData> * publisher = provider.underlying->getPublisher();
    kpsr::vision_ocv::FileImageStreamingService writeService(nullptr, publisher, TEST_DATA, true);

    kpsr::Subscriber<kpsr::vision_ocv::ImageData> * subscriber = provider.underlying->getSubscriber();
    SimpleReadService simpleReadService(nullptr, subscriber);
    SlowReadService slowReadService(nullptr, subscriber);

    //spdlog::info("Starting services.");
    writeService.start();
    simpleReadService.start();
    slowReadService.start();

    // Publish some integers.
    for (int i = 0; i < 50; i++) {
        //spdlog::info("Executing services.");
        writeService.execute();
        simpleReadService.execute();
        slowReadService.execute();
    }

    while (slowReadService.receivedEvents < 50) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    writeService.stop();
    simpleReadService.stop();
    slowReadService.stop();

    provider.underlying->stop();

    ASSERT_EQ(writeService.publishedEvents, 50);
    ASSERT_EQ(simpleReadService.receivedEvents, 50);
    ASSERT_EQ(slowReadService.receivedEvents, 50);
}

