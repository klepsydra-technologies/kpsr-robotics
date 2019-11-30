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

#include "gtest/gtest.h"

#include <klepsydra/core/service.h>
#include <klepsydra/core/publisher.h>
#include <klepsydra/core/subscriber.h>
#include <klepsydra/core/event_emitter_middleware_provider.h>

#include <klepsydra/dds_core/from_dds_middleware_provider.h>
#include <klepsydra/dds_core/to_dds_middleware_provider.h>

#include <klepsydra/dds_sensors/laser_scan_event_dds_mapper.h>

#include "laser_scan_event_subscriber_service.h"
#include "laser_scan_event_publisher_service.h"

TEST(DdsSensorsTest, DdsSensorsTest) {
    dds::domain::DomainParticipant dp(0);
    dds::topic::Topic<kpsr_dds_sensors::LaserScanEvent> topic(dp, "telemetry");
    dds::pub::Publisher pub(dp);
    dds::pub::DataWriter<kpsr_dds_sensors::LaserScanEvent> dw(pub, topic);

    kpsr::dds_mdlw::ToDDSMiddlewareProvider ddsToProvider(nullptr);

    dds::sub::Subscriber sub(dp);
    dds::sub::DataReader<kpsr_dds_sensors::LaserScanEvent> dr(sub, topic);

    kpsr::dds_mdlw::FromDDSMiddlewareProvider ddsFromProvider;

    kpsr::Publisher<kpsr::sensors::LaserScanEvent> * laserScanEventToDDSChannel =
            ddsToProvider.getToMiddlewareChannel<kpsr::sensors::LaserScanEvent, kpsr_dds_sensors::LaserScanEvent>(
                "telemetry", 0, nullptr, &dw
                );

    LaserScanEventPublisherService laserScanEventPublisherService(nullptr, laserScanEventToDDSChannel);

    kpsr::EventEmitterMiddlewareProvider<kpsr::sensors::LaserScanEvent> sensorsProvider(nullptr, "telemetry", 0, nullptr, nullptr);
    ddsFromProvider.registerToTopic("telemetry", &dr, true, sensorsProvider.getPublisher());

    LaserScanEventSubscriberService laserScanEventSubscriberService(nullptr, sensorsProvider.getSubscriber());

    laserScanEventPublisherService.startup();
    laserScanEventSubscriberService.startup();

    for (unsigned int i = 0; i < 100; ++i) {
        laserScanEventPublisherService.runOnce();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
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
    ddsFromProvider.unregisterFromTopic("telemetry", &dr);
}
