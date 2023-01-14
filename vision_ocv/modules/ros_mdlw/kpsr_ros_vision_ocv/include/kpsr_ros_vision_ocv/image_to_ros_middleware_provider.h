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

#ifndef IMAGE_TO_ROS_MIDDLEWARE_PROVIDER_H
#define IMAGE_TO_ROS_MIDDLEWARE_PROVIDER_H

#include <map>
#include <memory>

#include <image_transport/image_transport.h>
#include <ros/ros.h>

#include <klepsydra/vision_ocv/image_event_data.h>

#include <kpsr_ros_core/to_ros_middleware_provider.h>

#include "image_ros_mapper.h"
#include "image_to_ros_channel.h"

namespace kpsr {
namespace vision_ocv {
namespace ros_mdlw {
/**
 * @brief The ImageToRosMiddlewareProvider class
 *
 * @copyright 2023 Klepsydra Technologies AG
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-vision-ros_mdlw-composition
 *
 * @details This class is a wizard for cretion of Klepsydra Vision to ROS publishers.
 * Its use is very straightforward, as the following example shows:
@code
    // Init ROS
    ros::init(argc, argv, "kpsr_ros_core_test");
    ros::NodeHandle nodeHandle;
    ros::Rate rate(100);

    // Init image transport and image topic
    image_transport::ImageTransport it_(nodeHandle);
    image_transport::Publisher imagePublisner = it_.advertise("test/image_raw", 1);

    // One-liner prover creation
    kpsr::vision_ocv::ros_mdlw::ImageToRosMiddlewareProvider toRosProvider(nullptr);

    // Retrieve a publisher
    kpsr::Publisher<kpsr::vision_ocv::ImageData> * kpsrPublisher = toRosProvider.getToMiddlewareChannel("kpsr_ros_vision_test_topic", 1, nullptr, imagePublisner);
@endcode
 *
 */
class ImageToRosMiddlewareProvider
{
public:
    /**
     * @brief ImageToRosMiddlewareProvider
     * @param container
     */
    ImageToRosMiddlewareProvider(Container *container)
        : _container(container)
    {}

    /**
     * @brief getToMiddlewareChannel
     * @param topic
     * @param poolSize
     * @param initializerFunction
     * @param publisher
     * @return
     */
    Publisher<kpsr::vision_ocv::ImageData> *getToMiddlewareChannel(
        const std::string &topic,
        int poolSize,
        std::function<void(sensor_msgs::Image &)> initializerFunction,
        image_transport::Publisher &publisher)
    {
        auto search = _publisherMap.find(topic);
        if (search != _publisherMap.end()) {
            std::shared_ptr<void> internalPointer = search->second;
            std::shared_ptr<Publisher<kpsr::vision_ocv::ImageData>> publisher =
                std::static_pointer_cast<Publisher<kpsr::vision_ocv::ImageData>>(internalPointer);
            return publisher.get();
        } else {
            ImageToRosChannel *toRosChannel = new ImageToRosChannel(_container,
                                                                    topic,
                                                                    poolSize,
                                                                    initializerFunction,
                                                                    publisher);
            std::shared_ptr<Publisher<kpsr::vision_ocv::ImageData>> publisher(
                new ToMiddlewareChannel<kpsr::vision_ocv::ImageData, sensor_msgs::Image>(
                    _container, "vision_ocv" + topic, toRosChannel));
            std::shared_ptr<void> internalPointer = std::static_pointer_cast<void>(publisher);
            _publisherMap[topic] = internalPointer;
            return publisher.get();
        }
    }

private:
    Container *_container;
    std::map<std::string, std::shared_ptr<void>> _publisherMap;
};
} // namespace ros_mdlw
} // namespace vision_ocv
} // namespace kpsr

#endif // IMAGE_TO_ROS_MIDDLEWARE_PROVIDER_H
