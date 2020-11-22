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

#include <klepsydra/zmq_core/from_zmq_middleware_provider.h>
#include <klepsydra/zmq_core/to_zmq_middleware_provider.h>

#include <klepsydra/zmq_sensors/laser_scan_event_serializer.h>

#include "laser_scan_event_subscriber_service.h"
#include "laser_scan_event_publisher_service.h"

TEST(ZmqSensorsTest, ZmqSensorsTest) {
    std::string serverUrl = "tcp://*:5556";
    std::string topic = "sensors";

    //  Prepare our context and publisher
    zmq::context_t context (1);
    zmq::socket_t publisher (context, ZMQ_PUB);
    publisher.bind(serverUrl);
    publisher.bind("ipc://sensors.ipc");

    kpsr::zmq_mdlw::ToZMQMiddlewareProvider toZMQMiddlewareProvider(nullptr, publisher);

    std::string clientUrl = "tcp://localhost:5556";

    //  Socket to talk to server
    spdlog::info("Collecting updates from telemetry server...\n");
    zmq::socket_t subscriber (context, ZMQ_SUB);

    subscriber.connect(clientUrl);
    subscriber.setsockopt(ZMQ_SUBSCRIBE, topic.c_str(), topic.size());

    //  Process 100 updates
    kpsr::zmq_mdlw::FromZmqMiddlewareProvider _fromZmqMiddlewareProvider;
    kpsr::zmq_mdlw::FromZmqChannel<std::string> * _jsonFromZMQProvider = _fromZmqMiddlewareProvider.getJsonFromMiddlewareChannel<kpsr::sensors::LaserScanEvent>(subscriber, 1);

    kpsr::Publisher<kpsr::sensors::LaserScanEvent> * laserScanEventToDDSChannel = toZMQMiddlewareProvider.getJsonToMiddlewareChannel<kpsr::sensors::LaserScanEvent>(topic);

    LaserScanEventPublisherService laserScanEventPublisherService(nullptr, laserScanEventToDDSChannel);

    kpsr::EventEmitterMiddlewareProvider<kpsr::sensors::LaserScanEvent> sensorsProvider(nullptr, "telemetry", 0, nullptr, nullptr);
    _jsonFromZMQProvider->registerToTopic(topic, sensorsProvider.getPublisher());

    LaserScanEventSubscriberService laserScanEventSubscriberService(nullptr, sensorsProvider.getSubscriber());

    _jsonFromZMQProvider->start();
    laserScanEventPublisherService.startup();
    laserScanEventSubscriberService.startup();

    for (unsigned int i = 0; i < 100; ++i) {
        laserScanEventPublisherService.runOnce();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (i == 0) {
            continue;
        }

        ASSERT_EQ(laserScanEventPublisherService.sensor.seq, laserScanEventSubscriberService.sensor.seq);
        ASSERT_EQ(laserScanEventPublisherService.sensor.frameId, laserScanEventSubscriberService.sensor.frameId);

        ASSERT_FLOAT_EQ(laserScanEventPublisherService.sensor.angle_min, laserScanEventSubscriberService.sensor.angle_min);
        ASSERT_FLOAT_EQ(laserScanEventPublisherService.sensor.angle_max, laserScanEventSubscriberService.sensor.angle_max);
        ASSERT_FLOAT_EQ(laserScanEventPublisherService.sensor.angle_increment, laserScanEventSubscriberService.sensor.angle_increment);
        ASSERT_FLOAT_EQ(laserScanEventPublisherService.sensor.time_increment, laserScanEventSubscriberService.sensor.time_increment);
        ASSERT_FLOAT_EQ(laserScanEventPublisherService.sensor.scan_time, laserScanEventSubscriberService.sensor.scan_time);
        ASSERT_FLOAT_EQ(laserScanEventPublisherService.sensor.range_min, laserScanEventSubscriberService.sensor.range_min);
        ASSERT_FLOAT_EQ(laserScanEventPublisherService.sensor.range_max, laserScanEventSubscriberService.sensor.range_max);

        ASSERT_EQ(laserScanEventPublisherService.sensor.ranges.size(), laserScanEventSubscriberService.sensor.ranges.size());
        ASSERT_FLOAT_EQ(laserScanEventPublisherService.sensor.ranges[0], laserScanEventSubscriberService.sensor.ranges[0]);

        ASSERT_EQ(laserScanEventPublisherService.sensor.intensities.size(), laserScanEventSubscriberService.sensor.intensities.size());
        ASSERT_FLOAT_EQ(laserScanEventPublisherService.sensor.intensities[0], laserScanEventSubscriberService.sensor.intensities[0]);
    }

    laserScanEventPublisherService.shutdown();
    laserScanEventSubscriberService.shutdown();

    _jsonFromZMQProvider->stop();
}
