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

#ifndef IMAGE_TO_ROS_MIDDLEWARE_PROVIDER_H
#define IMAGE_TO_ROS_MIDDLEWARE_PROVIDER_H

#include <map>
#include <memory>

#include <ros/ros.h>
#include <image_transport/image_transport.h>

#include <klepsydra/vision_ocv/image_event_data.h>

#include <kpsr_ros_core/to_ros_middleware_provider.h>

#include "image_ros_mapper.h"
#include "image_to_ros_channel.h"

namespace kpsr
{
namespace vision_ocv
{
namespace ros_mdlw
{
/**
 * @brief The ImageToRosMiddlewareProvider class
 *
 * @copyright Klepsydra Technologies 2019-2020.
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
class ImageToRosMiddlewareProvider {
public:

    /**
     * @brief ImageToRosMiddlewareProvider
     * @param container
     */
    ImageToRosMiddlewareProvider(Container * container)
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
    Publisher<kpsr::vision_ocv::ImageData> * getToMiddlewareChannel(std::string topic, int poolSize, std::function<void(sensor_msgs::Image &)> initializerFunction, image_transport::Publisher & publisher) {
        auto search = _publisherMap.find(topic);
        if (search != _publisherMap.end()) {
            std::shared_ptr<void> internalPointer = search->second;
            std::shared_ptr<Publisher<kpsr::vision_ocv::ImageData>> publisher = std::static_pointer_cast<Publisher<kpsr::vision_ocv::ImageData>>(internalPointer);
            return publisher.get();
        }
        else {
            ImageToRosChannel * toRosChannel = new ImageToRosChannel(_container, topic, poolSize, initializerFunction, publisher);
            std::shared_ptr<Publisher<kpsr::vision_ocv::ImageData>> publisher(new ToMiddlewareChannel<kpsr::vision_ocv::ImageData, sensor_msgs::Image>(_container, "vision_ocv" + topic, toRosChannel));
            std::shared_ptr<void> internalPointer = std::static_pointer_cast<void>(publisher);
            _publisherMap[topic] = internalPointer;
            return publisher.get();
        }
    }

private:
    Container * _container;
    std::map<std::string, std::shared_ptr<void>> _publisherMap;
};
}
}
}

#endif // IMAGE_TO_ROS_MIDDLEWARE_PROVIDER_H
