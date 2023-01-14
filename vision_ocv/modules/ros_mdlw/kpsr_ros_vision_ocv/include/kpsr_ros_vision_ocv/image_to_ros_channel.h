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

#ifndef IMAGE_TO_ROS_CHANNEL_H
#define IMAGE_TO_ROS_CHANNEL_H

#include <klepsydra/core/environment.h>
#include <klepsydra/core/object_pool_publisher.h>

#include <klepsydra/serialization/mapper.h>

#include <klepsydra/vision_ocv/image_event_data.h>

#include <image_transport/image_transport.h>
#include <ros/ros.h>

namespace kpsr {
namespace vision_ocv {
namespace ros_mdlw {
/**
 * @brief The ImageToRosChannel class
 *
 * @copyright 2023 Klepsydra Technologies AG
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-vision-ros_mdlw-composition
 *
 */
class ImageToRosChannel : public ObjectPoolPublisher<sensor_msgs::Image>
{
public:
    /**
     * @brief ImageToRosChannel
     * @param container
     * @param name
     * @param poolSize
     * @param initializerFunction
     * @param rosPublisher
     */
    ImageToRosChannel(Container *container,
                      const std::string &name,
                      int poolSize,
                      std::function<void(sensor_msgs::Image &)> initializerFunction,
                      image_transport::Publisher &rosPublisher)
        : ObjectPoolPublisher<sensor_msgs::Image>(container,
                                                  name,
                                                  "ROS",
                                                  poolSize,
                                                  initializerFunction,
                                                  nullptr)
        , _rosPublisher(rosPublisher)
    {}

protected:
    void internalPublish(const sensor_msgs::Image &message) { _rosPublisher.publish(message); }

    void internalPublish(std::shared_ptr<const sensor_msgs::Image> message)
    {
        _rosPublisher.publish(*message.get());
    }

private:
    image_transport::Publisher _rosPublisher;
};
} // namespace ros_mdlw
} // namespace vision_ocv
} // namespace kpsr
#endif
