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

#include <gtest/gtest.h>

#include <klepsydra/core/service.h>
#include <klepsydra/core/publisher.h>
#include <klepsydra/core/subscriber.h>
#include <klepsydra/core/event_emitter_middleware_provider.h>
#include <klepsydra/core/cache_listener.h>

#include <klepsydra/mem_core/basic_middleware_provider.h>

#include <klepsydra/zmq_core/zhelpers.hpp>
#include <klepsydra/zmq_core/from_zmq_middleware_provider.h>
#include <klepsydra/zmq_core/to_zmq_middleware_provider.h>

#include <klepsydra/serialization/binary_cereal_mapper.h>
#include <klepsydra/serialization/json_cereal_mapper.h>

#include <klepsydra/zmq_vision_ocv/image_event_data_zmq_mapper.h>
#include <klepsydra/vision_ocv/image_data_factory.h>

#include "simple_write_service.h"
#include "simple_read_service.h"

#include "config.h"

bool matIsEqual(const cv::Mat mat1, const cv::Mat mat2){
    // treat two empty mat as identical as well
    if (mat1.empty() && mat2.empty()) {
        return true;
    }
    // if dimensionality of two mat is not identical, these two mat is not identical
    if (mat1.cols != mat2.cols || mat1.rows != mat2.rows || mat1.dims != mat2.dims) {
        return false;
    }
    cv::Mat diff = mat1 != mat2;
    return (cv::sum(diff) == cv::Scalar(0,0,0,0));
}

TEST(ZmqVisionTest, ZmqVisionTest) {
    std::string serverUrl = "tcp://*:9001";
    std::string topic = "image_data";

    //  Prepare our context and publisher
    zmq::context_t context (1);
    zmq::socket_t publisher (context, ZMQ_PUB);
    publisher.bind(serverUrl);

    kpsr::zmq_mdlw::ToZMQMiddlewareProvider toZMQMiddlewareProvider(nullptr, publisher);
    kpsr::Publisher<kpsr::vision_ocv::ImageData> * toZMQPublisher = toZMQMiddlewareProvider.getBinaryToMiddlewareChannel<kpsr::vision_ocv::ImageData>(topic, 0);

    std::string clientUrl = "tcp://localhost:9001";

    zmq::socket_t subscriber (context, ZMQ_SUB);

    subscriber.connect(clientUrl);
    subscriber.setsockopt(ZMQ_SUBSCRIBE, topic.c_str(), topic.size());

    //  Process 100 updates
    kpsr::zmq_mdlw::FromZmqMiddlewareProvider _fromZmqMiddlewareProvider;
    kpsr::zmq_mdlw::FromZmqChannel<Base> * _binaryFromZMQProvider = _fromZmqMiddlewareProvider.getBinaryFromMiddlewareChannel<kpsr::vision_ocv::ImageData>(subscriber, 10);
    _binaryFromZMQProvider->start();

    kpsr::vision_ocv::ImageDataFactory factory(320, 480, 10, "body");

    SimpleWriteService imageDataPublisherService(nullptr, toZMQPublisher, TEST_DATA, true);


    imageDataPublisherService.startup();

    for (unsigned int i = 0; i < 2; ++i) {
        kpsr::EventEmitterMiddlewareProvider<kpsr::vision_ocv::ImageData> imageDataProvider(nullptr, topic, 0, factory.initializerFunction, nullptr);
        _binaryFromZMQProvider->registerToTopic(topic, imageDataProvider.getPublisher());

        SimpleReadService imageDataSubscriberService(nullptr, imageDataProvider.getSubscriber());
        imageDataSubscriberService.startup();
        imageDataPublisherService.runOnce();

        while (!imageDataSubscriberService.receivedImage) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        imageDataSubscriberService.receivedImage = false;
        EXPECT_TRUE(matIsEqual(imageDataPublisherService.imageEvent.img, imageDataSubscriberService.lastReadImg.img));
        imageDataSubscriberService.lastReadImg.img =  cv::Scalar(0,0,0,0);
        imageDataSubscriberService.stop();
    }
    _binaryFromZMQProvider->stop();
    _binaryFromZMQProvider->unregisterFromTopic(topic);
    imageDataPublisherService.stop();
}
