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

#ifndef SIMPLE_READ_SERVICE_H
#define SIMPLE_READ_SERVICE_H

#include <opencv2/core/core.hpp>

#include <spdlog/spdlog.h>

#include <klepsydra/core/service.h>
#include <klepsydra/core/subscriber.h>

#include <klepsydra/vision_ocv/image_event_data.h>

namespace kpsr {
namespace vision_ocv {
class SimpleReadService : public kpsr::Service
{
public:
    SimpleReadService(kpsr::Environment *environment,
                      kpsr::Subscriber<kpsr::vision_ocv::ImageData> *subscriber);

    void start();

    void stop();

    void execute() {}

    void onEventReceived(const kpsr::vision_ocv::ImageData &event);

    bool receivedImage = false;
    kpsr::vision_ocv::ImageData lastReadImg;

private:
    kpsr::Subscriber<kpsr::vision_ocv::ImageData> *_subscriber;
    long _startTimestamp;
};
} // namespace vision_ocv
} // namespace kpsr

#endif // SIMPLE_READ_SERVICE_H
