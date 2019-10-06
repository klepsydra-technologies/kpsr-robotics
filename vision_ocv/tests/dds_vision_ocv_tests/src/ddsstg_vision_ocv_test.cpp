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

#include <klepsydra/dds_core/from_dds_middleware_provider.h>
#include <klepsydra/dds_core/to_dds_middleware_provider.h>

#include <klepsydra/dds_vision_ocv/image_event_data_dds_mapper.h>
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
    return (cv::sum(diff) == cv::Scalar(0,0,0,0));;
}

TEST(DdsVisionTest, DdsVisionTest) {
    dds::domain::DomainParticipant dp(0);
    dds::topic::Topic<kpsr_dds_vision_ocv::ImageData> topic(dp, "image_data");
    dds::pub::Publisher pub(dp);
    dds::pub::DataWriter<kpsr_dds_vision_ocv::ImageData> dw(pub, topic);

    kpsr::dds_mdlw::ToDDSMiddlewareProvider ddsToProvider(nullptr);

    dds::sub::Subscriber sub(dp);
    dds::sub::DataReader<kpsr_dds_vision_ocv::ImageData> dr(sub, topic);

    kpsr::dds_mdlw::FromDDSMiddlewareProvider ddsFromProvider;

    kpsr::Publisher<kpsr::vision_ocv::ImageData> * imageDataToDDSChannel =
            ddsToProvider.getToMiddlewareChannel<kpsr::vision_ocv::ImageData, kpsr_dds_vision_ocv::ImageData>(
                "image_data", 0, nullptr, &dw
                );

    kpsr::vision_ocv::ImageDataFactory factory(320, 480, 10, "body");

    SimpleWriteService imageDataPublisherService(nullptr, imageDataToDDSChannel, TEST_DATA, true);

    kpsr::EventEmitterMiddlewareProvider<kpsr::vision_ocv::ImageData> imageDataProvider(nullptr, "image_data", 0, factory.initializerFunction, nullptr);
    ddsFromProvider.registerToTopic("image_data", &dr, true, imageDataProvider.getPublisher());

    SimpleReadService imageDataSubscriberService(nullptr, imageDataProvider.getSubscriber());

    imageDataPublisherService.startup();
    imageDataSubscriberService.startup();

    for (unsigned int i = 0; i < 100; ++i) {
        imageDataPublisherService.runOnce();
        while (!imageDataSubscriberService.receivedImage) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        imageDataSubscriberService.receivedImage = false;
        ASSERT_TRUE(matIsEqual(imageDataPublisherService.imageEvent.img, imageDataSubscriberService.lastReadImg.img));
    }

    ddsFromProvider.unregisterFromTopic("image_data", &dr);
}
