#include <string>

#include "std_msgs/String.h"
#include <gtest/gtest.h>

#include <klepsydra/mem_core/basic_middleware_provider.h>
#include <klepsydra/core/cache_listener.h>

#include <kpsr_ros_core/to_ros_middleware_provider.h>
#include <kpsr_ros_core/from_ros_middleware_provider.h>

#include <kpsr_ros_serialization/primitive_type_ros_mapper.h>

TEST(KpsrRosCoreTest, nominalCaseNoPool) {

    int argc = 0;
    char ** argv = nullptr;

    ros::init(argc, argv, "kpsr_ros_core_test");
    ros::NodeHandle nodeHandle;
    ros::Rate rate(100);

    ros::Publisher stringPublisher = nodeHandle.advertise<std_msgs::String>("kpsr_ros_core_test_topic", 1);

    kpsr::ros_mdlw::ToRosMiddlewareProvider toRosProvider(nullptr);

    kpsr::Publisher<std::string> * kpsrPublisher = toRosProvider.getToMiddlewareChannel<std::string, std_msgs::String>("kpsr_ros_core_test_topic", 1, nullptr, stringPublisher);

    kpsr::mem::BasicMiddlewareProvider<std::string> safeQueueProvider(nullptr, "test", 8, 0, nullptr, nullptr, false);
    safeQueueProvider.start();

    kpsr::ros_mdlw::FromRosMiddlewareProvider fromRosProvider(nodeHandle);
    fromRosProvider.registerToTopic<std::string, std_msgs::String>("kpsr_ros_core_test_topic", 1, safeQueueProvider.getPublisher());

    kpsr::mem::CacheListener<std::string> cacheListener;
    safeQueueProvider.getSubscriber()->registerListener("cacheListener", cacheListener.cacheListenerFunction);

    ASSERT_EQ(cacheListener.counter, 0);

    kpsrPublisher->publish("hola.1");
    ros::spinOnce();
    rate.sleep();
    kpsrPublisher->publish("hola.2");
    ros::spinOnce();
    rate.sleep();
    kpsrPublisher->publish("hola.3");
    ros::spinOnce();
    rate.sleep();
    kpsrPublisher->publish("hola.4");
    ros::spinOnce();
    rate.sleep();
    kpsrPublisher->publish("hola.5");
    ros::spinOnce();
    rate.sleep();

    while (cacheListener.counter < 5) {
        ros::spinOnce();
        rate.sleep();
    }

    safeQueueProvider.stop();

    ASSERT_EQ(cacheListener.counter, 5);
    ASSERT_EQ(*cacheListener.getLastReceivedEvent().get(), "hola.5");
}

