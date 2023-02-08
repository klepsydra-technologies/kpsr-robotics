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

#include "config.h"
#include <benchmark/benchmark.h>
#include <klepsydra/core/event_emitter_middleware_provider.h>
#include <klepsydra/high_performance/event_loop_middleware_provider.h>
#include <klepsydra/vision_ocv/file_image_stream_service.h>
#include <klepsydra/vision_ocv/image_data_factory.h>
#include <opencv2/opencv.hpp>
#include <spdlog/fmt/bundled/color.h>
#include <spdlog/spdlog.h>
class FactoryPerformanceTest : public benchmark::Fixture
{
public:
    FactoryPerformanceTest()
        : benchmark::Fixture()
    {
        auto formattedMessage =
            fmt::format(fmt::fg(fmt::terminal_color::green) | fmt::emphasis::bold,
                        "Please notice that pool size 0 also means using the factory.");
        spdlog::info("{}", formattedMessage);
        spdlog::set_level(spdlog::level::level_enum::err);
    }
    ~FactoryPerformanceTest() {}

    void SetUp(const ::benchmark::State &state)
    {
        int poolSize = state.range(0);
        bool useEventLoop = state.range(1);
        bool withFactory = poolSize == 0;
        width = state.range(2);
        height = width;

        eventsListened = 0;
        if (withFactory) {
            imageDataFactory.reset(
                new kpsr::vision_ocv::ImageDataFactory(width,
                                                       height,
                                                       cv::IMREAD_REDUCED_GRAYSCALE_2,
                                                       "raw_image"));
            _buildFunction = imageDataFactory->initializerFunction;
            _cloneFunction = imageDataFactory->eventClonerFunction;
        } else {
            _buildFunction = nullptr;
            _cloneFunction = [](const kpsr::vision_ocv::ImageData &src,
                                kpsr::vision_ocv::ImageData &dst) { dst.clone(src); };
        }

        if (useEventLoop) {
            _eventLoopProvider.reset(
                new kpsr::high_performance::EventLoopMiddlewareProvider<16>(nullptr, "img"));
            _eventLoopProvider->start();

            subscriber = _eventLoopProvider->getSubscriber<kpsr::vision_ocv::ImageData>(
                "imageEvent");
            publisher = _eventLoopProvider
                            ->getPublisher<kpsr::vision_ocv::ImageData>("imageEvent",
                                                                        poolSize,
                                                                        _buildFunction,
                                                                        _cloneFunction);
        } else {
            _eventEmitterProvider.reset(
                new kpsr::EventEmitterMiddlewareProvider<kpsr::vision_ocv::ImageData>(
                    nullptr, "img", poolSize, _buildFunction, _cloneFunction));

            subscriber = _eventEmitterProvider->getSubscriber();
            publisher = _eventEmitterProvider->getPublisher();
        }
    }

    void TearDown(const ::benchmark::State &state)
    {
        subscriber->removeListener("receiveIm");
        bool useEventLoop = state.range(1);
        if (useEventLoop) {
            _eventLoopProvider->stop();
        }
    }

    void setListener(benchmark::State &state)
    {
        subscriber
            ->registerListener("receiveIm", [&state, this](const kpsr::vision_ocv::ImageData &im) {
                auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
                               std::chrono::system_clock::now().time_since_epoch())
                               .count();
                state.SetIterationTime(double(now - im.timestamp) / 1E3);
                eventsListened++;
            });
    }
    int width, height;
    kpsr::Subscriber<kpsr::vision_ocv::ImageData> *subscriber;
    kpsr::Publisher<kpsr::vision_ocv::ImageData> *publisher;
    std::atomic<int> eventsListened; // To be removed when pub/sub params has been implemented
    std::unique_ptr<kpsr::vision_ocv::ImageDataFactory> imageDataFactory;

private:
    std::function<void(kpsr::vision_ocv::ImageData &)> _buildFunction;
    std::function<void(const kpsr::vision_ocv::ImageData &, kpsr::vision_ocv::ImageData &)>
        _cloneFunction;
    std::unique_ptr<kpsr::EventEmitterMiddlewareProvider<kpsr::vision_ocv::ImageData>>
        _eventEmitterProvider;
    std::unique_ptr<kpsr::high_performance::EventLoopMiddlewareProvider<16>> _eventLoopProvider;
};

BENCHMARK_DEFINE_F(FactoryPerformanceTest, SimpleTest)(benchmark::State &state)
{
    bool useEventLoop = state.range(1);
    setListener(state);

    int eventsPublished = 0;

    kpsr::vision_ocv::ImageData event;
    imageDataFactory->initializerFunction(event);

    for (auto _ : state) {
        event.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                              std::chrono::system_clock::now().time_since_epoch())
                              .count();
        publisher->publish(event);
        eventsPublished++;
        int failSafeCounter = 0;
        const int failSafeMaxIterations = 10;
        while (useEventLoop && (eventsListened.load() < eventsPublished) &&
               (failSafeCounter++ < failSafeMaxIterations)) {
            // TODO: Change loop condition to use events parameters from pub/sub objects
            // Same with the other functions
            std::this_thread::sleep_for(std::chrono::microseconds(1));
        }
    }

    state.counters["publishedEvents"] = eventsPublished;
    state.counters["listenerEvents"] = eventsListened.load();
}

BENCHMARK_DEFINE_F(FactoryPerformanceTest, ReadingFromDiskTest)(benchmark::State &state)
{
    bool useEventLoop = state.range(1);
    setListener(state);

    int eventsPublished = 0;

    kpsr::vision_ocv::FileImageStreamingService streamService(nullptr,
                                                              publisher,
                                                              TEST_DATA,
                                                              true,
                                                              width,
                                                              height,
                                                              "raw_image",
                                                              "serviceStream");
    streamService.startup();

    for (auto _ : state) {
        streamService.runOnce();
        eventsPublished++;
        int failSafeCounter = 0;
        const int failSafeMaxIterations = 10;
        while (useEventLoop && (eventsListened.load() < eventsPublished) &&
               (failSafeCounter++ < failSafeMaxIterations)) {
            std::this_thread::sleep_for(std::chrono::microseconds(1));
        }
    }

    state.counters["publishedEvents"] = eventsPublished;
    state.counters["listenerEvents"] = eventsListened.load();

    streamService.shutdown();
}

BENCHMARK_REGISTER_F(FactoryPerformanceTest, SimpleTest)
    ->UseManualTime()
    ->Unit(benchmark::kMillisecond)
    ->ArgsProduct({{0, 4}, {false, true}, {1000, 3500, 5500, 7500, 10000}})
    ->ArgNames({"PoolSize", "WithEventLoop", "ImageSize"});
BENCHMARK_REGISTER_F(FactoryPerformanceTest, ReadingFromDiskTest)
    ->UseManualTime()
    ->Unit(benchmark::kMillisecond)
    ->ArgsProduct({{0, 4}, {false, true}, {1000, 3500, 5500, 7500, 10000}})
    ->ArgNames({"PoolSize", "WithEventLoop", "ImageSize"});
BENCHMARK_MAIN();
