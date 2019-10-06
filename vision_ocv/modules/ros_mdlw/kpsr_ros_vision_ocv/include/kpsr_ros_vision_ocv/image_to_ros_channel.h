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

#ifndef IMAGE_TO_ROS_CHANNEL_H
#define IMAGE_TO_ROS_CHANNEL_H

#include <klepsydra/core/environment.h>
#include <klepsydra/core/object_pool_publisher.h>

#include <klepsydra/serialization/mapper.h>

#include <klepsydra/vision_ocv/image_event_data.h>

#include <ros/ros.h>
#include <image_transport/image_transport.h>

namespace kpsr
{
namespace vision_ocv
{
namespace ros_mdlw
{
/**
 * @brief The ImageToRosChannel class
 *
 * @copyright Klepsydra Technologies 2019-2020.
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
    ImageToRosChannel(Container * container, std::string name, int poolSize, std::function<void(sensor_msgs::Image &)> initializerFunction, image_transport::Publisher & rosPublisher)
        : ObjectPoolPublisher<sensor_msgs::Image>(container, name, "ROS", poolSize, initializerFunction, nullptr)
        , _rosPublisher(rosPublisher)
    {}

protected:
    void internalPublish(const sensor_msgs::Image & message) {
        _rosPublisher.publish(message);
    }

    void internalPublish(std::shared_ptr<const sensor_msgs::Image> message) {
        _rosPublisher.publish(* message.get());
    }
private:
    image_transport::Publisher _rosPublisher;
};
}
}
}
#endif
