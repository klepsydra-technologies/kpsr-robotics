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
