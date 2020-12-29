#include <gtest/gtest.h>

#include <klepsydra/core/service.h>
#include <klepsydra/core/publisher.h>
#include <klepsydra/core/subscriber.h>
#include <klepsydra/mem_core/basic_middleware_provider.h>

#include "image_to_ros_middleware_provider.h"
#include "image_ros_mapper.h"

#include "image_from_ros_middleware_provider.h"
#include <klepsydra/vision_ocv/image_data_factory.h>

#include <klepsydra/vision_ocv/file_image_stream_service.h>

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

TEST(KpsrRosCoreTest, nominalCaseNoPool) {

    int argc = 0;
    char ** argv = nullptr;

    ros::init(argc, argv, "kpsr_ros_core_test");
    ros::NodeHandle nodeHandle;
    ros::Rate rate(100);

    image_transport::ImageTransport it_(nodeHandle);
    image_transport::Publisher imagePublisner = it_.advertise("test/image_raw", 1);

    kpsr::vision_ocv::ros_mdlw::ImageToRosMiddlewareProvider toRosProvider(nullptr);

    kpsr::Publisher<kpsr::vision_ocv::ImageData> * kpsrPublisher = toRosProvider.getToMiddlewareChannel("kpsr_ros_vision_test_topic", 1, nullptr, imagePublisner);

    kpsr::vision_ocv::ros_mdlw::ImageFromRosMiddlewareProvider fromRosProvider(it_);

    kpsr::vision_ocv::ImageDataFactory factory(320, 480, 10, "body");

    kpsr::vision_ocv::FileImageStreamingService imageDataPublisherService(nullptr, kpsrPublisher, TEST_DATA, true);

    kpsr::mem::BasicMiddlewareProvider<kpsr::vision_ocv::ImageData> imageDataProvider(nullptr, "test", 8, 0, nullptr, nullptr, false);
    imageDataProvider.start();
    fromRosProvider.registerToTopic("test/image_raw", 1, imageDataProvider.getPublisher());

    SimpleReadService imageDataSubscriberService(nullptr, imageDataProvider.getSubscriber());

    imageDataPublisherService.startup();
    imageDataSubscriberService.startup();

    for (unsigned int i = 0; i < 100; ++i) {
        imageDataPublisherService.runOnce();
        while (!imageDataSubscriberService.receivedImage) {
		    ros::spinOnce();
		    rate.sleep();
        }
        imageDataSubscriberService.receivedImage = false;
        ASSERT_TRUE(matIsEqual(imageDataPublisherService.imageEvent.img, imageDataSubscriberService.lastReadImg.img));
    }
}
