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

#include <klepsydra/dds_geometry/pose_event_dds_mapper.h>

#include "pose_event_publisher_service.h"
#include "pose_event_subscriber_service.h"

TEST(DdsGeometryTest, DdsGeometryTest) {
    dds::domain::DomainParticipant dp(0);
    dds::topic::Topic<kpsr_dds_geometry::PoseEventData> topic(dp, "telemetry");
    dds::pub::Publisher pub(dp);
    dds::pub::DataWriter<kpsr_dds_geometry::PoseEventData> dw(pub, topic);

    kpsr::dds_mdlw::ToDDSMiddlewareProvider ddsToProvider(nullptr);

    dds::sub::Subscriber sub(dp);
    dds::sub::DataReader<kpsr_dds_geometry::PoseEventData> dr(sub, topic);

    kpsr::dds_mdlw::FromDDSMiddlewareProvider ddsFromProvider;

    kpsr::Publisher<kpsr::geometry::PoseEventData> * poseEventDataToDDSChannel =
            ddsToProvider.getToMiddlewareChannel<kpsr::geometry::PoseEventData, kpsr_dds_geometry::PoseEventData>(
                "telemetry", 0, nullptr, &dw
                );

    PoseEventDataPublisherService poseEventDataPublisherService(nullptr, poseEventDataToDDSChannel);

    kpsr::EventEmitterMiddlewareProvider<kpsr::geometry::PoseEventData> geometryProvider(nullptr, "telemetry", 0, nullptr, nullptr);
    ddsFromProvider.registerToTopic("telemetry", &dr, true, geometryProvider.getPublisher());

    PoseEventDataSubscriberService poseEventDataSubscriberService(nullptr, geometryProvider.getSubscriber());

    poseEventDataPublisherService.startup();
    poseEventDataSubscriberService.startup();

    for (unsigned int i = 0; i < 100; ++i) {
        poseEventDataPublisherService.runOnce();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
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

    ddsFromProvider.unregisterFromTopic("telemetry", &dr);
}
