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

#include <stdio.h>
#include <thread>
#include <unistd.h>
#include <math.h>

#include <sstream>
#include <fstream>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

#include "gtest/gtest.h"

#include <klepsydra/core/service.h>
#include <klepsydra/core/publisher.h>
#include <klepsydra/core/subscriber.h>
#include <klepsydra/core/event_emitter_middleware_provider.h>

#include <klepsydra/serialization/json_cereal_mapper.h>

#include <klepsydra/zmq_core/zhelpers.hpp>
#include <klepsydra/zmq_core/from_zmq_middleware_provider.h>
#include <klepsydra/zmq_core/to_zmq_middleware_provider.h>

#include <klepsydra/zmq_geometry/pose_event_data_serializer.h>

#include "pose_event_publisher_service.h"
#include "pose_event_subscriber_service.h"

TEST(ZmqGeometryTest, ZmqGeometryTest) {
    std::string serverUrl = "tcp://*:5556";
    std::string topic = "geometry";

    //  Prepare our context and publisher
    zmq::context_t context (1);
    zmq::socket_t publisher (context, ZMQ_PUB);
    publisher.bind(serverUrl);
    publisher.bind("ipc://geometry.ipc");

    kpsr::zmq_mdlw::ToZMQMiddlewareProvider toZMQMiddlewareProvider(nullptr, publisher);
    kpsr::Publisher<kpsr::geometry::PoseEventData> * toZMQPublisher = toZMQMiddlewareProvider.getJsonToMiddlewareChannel<kpsr::geometry::PoseEventData>(topic, 0);

    std::string clientUrl = "tcp://localhost:5556";

    //  Socket to talk to server
    spdlog::info("Collecting updates from telemetry server...\n");
    zmq::socket_t subscriber (context, ZMQ_SUB);

    subscriber.connect(clientUrl);
    subscriber.setsockopt(ZMQ_SUBSCRIBE, topic.c_str(), topic.size());

    //  Process 100 updates
    kpsr::zmq_mdlw::FromZmqMiddlewareProvider _fromZmqMiddlewareProvider;
    kpsr::zmq_mdlw::FromZmqChannel<std::string> * _jsonFromZMQProvider = _fromZmqMiddlewareProvider.getJsonFromMiddlewareChannel<kpsr::geometry::PoseEventData>(subscriber, 1);

    kpsr::Publisher<kpsr::geometry::PoseEventData> * poseEventDataToDDSChannel = toZMQMiddlewareProvider.getJsonToMiddlewareChannel<kpsr::geometry::PoseEventData>(topic);

    PoseEventDataPublisherService poseEventDataPublisherService(nullptr, poseEventDataToDDSChannel);

    kpsr::EventEmitterMiddlewareProvider<kpsr::geometry::PoseEventData> geometryProvider(nullptr, "telemetry", 0, nullptr, nullptr);
    _jsonFromZMQProvider->registerToTopic(topic, geometryProvider.getPublisher());

    PoseEventDataSubscriberService poseEventDataSubscriberService(nullptr, geometryProvider.getSubscriber());

    _jsonFromZMQProvider->start();
    poseEventDataPublisherService.startup();
    poseEventDataSubscriberService.startup();

    for (unsigned int i = 0; i < 100; ++i) {
        poseEventDataPublisherService.runOnce();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (i == 0) {
            continue;
        }

        ASSERT_EQ(poseEventDataPublisherService.sensor.seq, poseEventDataSubscriberService.sensor.seq);
        ASSERT_EQ(poseEventDataPublisherService.sensor.frameId, poseEventDataSubscriberService.sensor.frameId);
        ASSERT_FLOAT_EQ(poseEventDataPublisherService.sensor.x, poseEventDataSubscriberService.sensor.x);
        ASSERT_FLOAT_EQ(poseEventDataPublisherService.sensor.y, poseEventDataSubscriberService.sensor.y);
        ASSERT_FLOAT_EQ(poseEventDataPublisherService.sensor.z, poseEventDataSubscriberService.sensor.z);

        ASSERT_EQ(poseEventDataPublisherService.sensor.eulerAvailable, poseEventDataSubscriberService.sensor.eulerAvailable);
        ASSERT_FLOAT_EQ(poseEventDataPublisherService.sensor.roll, poseEventDataSubscriberService.sensor.roll);
        ASSERT_FLOAT_EQ(poseEventDataPublisherService.sensor.pitch, poseEventDataSubscriberService.sensor.pitch);
        ASSERT_FLOAT_EQ(poseEventDataPublisherService.sensor.yaw, poseEventDataSubscriberService.sensor.yaw);

        ASSERT_EQ(poseEventDataPublisherService.sensor.posCovarianceAvailable, poseEventDataSubscriberService.sensor.posCovarianceAvailable);
        ASSERT_EQ(poseEventDataPublisherService.sensor.positionCovariance.size(), poseEventDataSubscriberService.sensor.positionCovariance.size());
        ASSERT_FLOAT_EQ(poseEventDataPublisherService.sensor.positionCovariance[0], poseEventDataSubscriberService.sensor.positionCovariance[0]);
        ASSERT_FLOAT_EQ(poseEventDataPublisherService.sensor.positionCovariance[1], poseEventDataSubscriberService.sensor.positionCovariance[1]);
        ASSERT_FLOAT_EQ(poseEventDataPublisherService.sensor.positionCovariance[2], poseEventDataSubscriberService.sensor.positionCovariance[2]);
    }

    poseEventDataPublisherService.shutdown();
    poseEventDataSubscriberService.shutdown();

    _jsonFromZMQProvider->stop();
}
