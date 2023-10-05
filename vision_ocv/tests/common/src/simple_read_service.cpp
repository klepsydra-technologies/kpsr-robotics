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

#include <opencv2/highgui/highgui.hpp>
#include <simple_read_service.h>

#include <spdlog/spdlog.h>

kpsr::vision_ocv::SimpleReadService::SimpleReadService(
    kpsr::Environment *environment, kpsr::Subscriber<kpsr::vision_ocv::ImageData> *subscriber)
    : kpsr::Service(nullptr, environment, "SimpleReadService")
    , _subscriber(subscriber)
{}

void kpsr::vision_ocv::SimpleReadService::start()
{
    std::function<void(kpsr::vision_ocv::ImageData)> simpleListener =
        std::bind(&SimpleReadService::onEventReceived, this, std::placeholders::_1);
    this->_subscriber->registerListener("SimpleReadService", simpleListener);
}

void kpsr::vision_ocv::SimpleReadService::stop()
{
    this->_subscriber->removeListener("SimpleReadService");
}

void kpsr::vision_ocv::SimpleReadService::onEventReceived(const kpsr::vision_ocv::ImageData &event)
{
    spdlog::info("SimpleReadService. event received. {}"
                 ". image type: {}"
                 ". image rows: {}"
                 ". image cols: {}",
                 event.seq,
                 event.img.type(),
                 event.img.rows,
                 event.img.cols);
    lastReadImg = event;
    receivedImage = true;
}
