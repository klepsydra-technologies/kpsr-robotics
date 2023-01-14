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

#include <klepsydra/core/event_emitter_middleware_provider.h>

#include <klepsydra/vision_ocv/file_image_stream_service.h>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include "gtest/gtest.h"

#include "config.h"

#include <klepsydra/vision_ocv/mpeg_writer.h>

TEST(VideoStreamingTest, BasicStreamingTest)
{
    kpsr::EventEmitterMiddlewareProvider<kpsr::vision_ocv::ImageData>
        imageEventEmitter(nullptr, "image_provider", 0, nullptr, nullptr);
    kpsr::EventEmitterMiddlewareProvider<std::vector<uchar>>
        encodedImageEventEmitter(nullptr, "encoded_image_provider", 0, nullptr, nullptr);

    kpsr::vision_ocv::FileImageStreamingService writeService(nullptr,
                                                             imageEventEmitter.getPublisher(),
                                                             TEST_DATA,
                                                             true);

    kpsr::vision_ocv::MJPEGWriter streamingService(8080,
                                                   180000,
                                                   95,
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
