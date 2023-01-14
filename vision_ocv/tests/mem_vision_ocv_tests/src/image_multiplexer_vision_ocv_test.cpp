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

#include <thread>

#include <klepsydra/mem_vision_ocv/image_multiplexer_vision_ocv_provider.h>

#include <klepsydra/vision_ocv/file_image_stream_service.h>

#include "simple_read_service.h"
#include "slow_read_service.h"

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"

#include "gtest/gtest.h"

#include "config.h"

TEST(HPVisionTest, HPVisionTest)
{
    kpsr::vision_ocv::high_performance::ImageMultiplexerVisionMiddlewareProvider<128>
        provider(nullptr, "test", 1080, 2040, 16, "body");

    //spdlog::info("Creating services.");
    kpsr::Publisher<kpsr::vision_ocv::ImageData> *publisher = provider.underlying->getPublisher();
    kpsr::vision_ocv::FileImageStreamingService writeService(nullptr, publisher, TEST_DATA, true);

    kpsr::Subscriber<kpsr::vision_ocv::ImageData> *subscriber = provider.underlying->getSubscriber(
        "test");
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

    int numAttempts = 10;
    for (int i = 0; i < numAttempts; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (simpleReadService.receivedEvents == 50)
            break;
    }

    writeService.stop();
    simpleReadService.stop();
    slowReadService.stop();

    ASSERT_EQ(writeService.publishedEvents, 50);
    ASSERT_EQ(simpleReadService.receivedEvents, 50);
    ASSERT_EQ(slowReadService.receivedEvents, 50);
}
