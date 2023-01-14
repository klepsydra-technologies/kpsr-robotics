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

#ifndef IMAGE_FROM_ROS_MIDDLEWARE_PROVIDER_H
#define IMAGE_FROM_ROS_MIDDLEWARE_PROVIDER_H

#include <map>
#include <memory>

#include <klepsydra/core/event_emitter_subscriber.h>

#include "ros/ros.h"
#include <image_transport/image_transport.h>

#include <kpsr_ros_core/from_ros_middleware_provider.h>

namespace kpsr {
namespace vision_ocv {
namespace ros_mdlw {
/**
 * @brief The ImageRosSubscriptionData struct
 *
 * @copyright 2023 Klepsydra Technologies AG
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-ros_mdlw-vision-internal
 *
 */
struct ImageRosSubscriptionData
{
public:
    /**
    * @brief ImageRosSubscriptionData
    * @param imageTransport
    * @param topicName
    * @param queueSize
    * @param internalPublisher
    */
    ImageRosSubscriptionData(image_transport::ImageTransport imageTransport,
                             const char *topicName,
                             int queueSize,
                             Publisher<kpsr::vision_ocv::ImageData> *internalPublisher)
        : _fromMiddlewareChannel(internalPublisher)
    {
        _rosSubscriber = imageTransport.subscribe(topicName,
                                                  queueSize,
                                                  &ImageRosSubscriptionData::imageCallback,
                                                  this);
    }

private:
    void imageCallback(const sensor_msgs::ImageConstPtr &msg)
    {
        _fromMiddlewareChannel.onMiddlewareMessage(*msg.get());
    }

    FromMiddlewareChannel<kpsr::vision_ocv::ImageData, sensor_msgs::Image> _fromMiddlewareChannel;
    image_transport::Subscriber _rosSubscriber;
};

/**
 * @brief The ImageFromRosMiddlewareProvider class
 *
 * @copyright 2023 Klepsydra Technologies AG
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-vision-ros_mdlw-composition
 *
 * @details ROS middleware to Klepsydra adapter or channel for images. Its use is very straightforward as
 * per the following example:
 *
@code
    // Initialize ROS
    image_transport::ImageTransport imageTranport(nodeHandle);

    // Create a from ros provider Klepsydra wizard instance. Once for the whole application.
    kpsr::ros_mdlw::ImageFromRosMiddlewareProvider fromRosProvider(imageTranport);

    // Create a Klepsydra pub/sub pair
    kpsr::mem_mdlw::SafeQueueMiddlewareProvider<kpsr::vision_ocv::ImageData> safeQueueProvider(nullptr, "test", 8, 0, nullptr, nullptr, false);
    safeQueueProvider.start();

    // Obtain a from ros channel and provide the klepsydra publisher
    fromRosProvider.registerToTopic("kpsr_ros_core_test_topic", 1, safeQueueProvider.getPublisher());

    // Now, listeners can be registered to the corresponding subscriber.
    kpsr::mem_mdlw::CacheListener<kpsr::vision_ocv::ImageData> cacheListener;
    safeQueueProvider.getSubscriber()->registerListener("cacheListener", cacheListener.cacheListenerFunction);
@endcode
 *
 */
class ImageFromRosMiddlewareProvider
{
public:
    /**
     * @brief ImageFromRosMiddlewareProvider
     * @param imageTransport
     */
    ImageFromRosMiddlewareProvider(image_transport::ImageTransport &imageTransport)
        : _imageTransport(imageTransport)
    {}

    /**
     * @brief registerToTopic
     * @param topicName
     * @param queueSize
     * @param internalPublisher
     */
    void registerToTopic(const char *topicName,
                         int queueSize,
                         Publisher<kpsr::vision_ocv::ImageData> *internalPublisher)
    {
        auto search = _subscriberMap.find(topicName);
        if (search == _subscriberMap.end()) {
            std::shared_ptr<ImageRosSubscriptionData> rosSubscriptionData =
                std::shared_ptr<ImageRosSubscriptionData>(
                    new ImageRosSubscriptionData(_imageTransport,
                                                 topicName,
                                                 queueSize,
                                                 internalPublisher));
            std::shared_ptr<void> internalPointer = std::static_pointer_cast<void>(
                rosSubscriptionData);
            _subscriberMap[topicName] = internalPointer;
        }
    }

private:
    image_transport::ImageTransport &_imageTransport;
    std::map<std::string, std::shared_ptr<void>> _subscriberMap;
};
} // namespace ros_mdlw
} // namespace vision_ocv
} // namespace kpsr
#endif
