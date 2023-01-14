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

#ifndef IMAGE_ROS_MAPPER_H
#define IMAGE_ROS_MAPPER_H

#include <atomic>

#include "ros/ros.h"

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"

#include <image_transport/image_transport.h>

#include <cv_bridge/cv_bridge.h>

#include <klepsydra/serialization/mapper.h>

#include <klepsydra/vision_ocv/image_event_data.h>

#include "image_encoding_helper.h"

namespace kpsr {
template<>
/**
 * @brief The Mapper<kpsr::vision_ocv::ImageData, sensor_msgs::Image> class
 *
 * @copyright 2023 Klepsydra Technologies AG
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-vision-ros_mdlw-composition
 *
 */
class Mapper<kpsr::vision_ocv::ImageData, sensor_msgs::Image>
{
public:
    /**
     * @brief toMiddleware
     * @param event
     * @param message
     */
    void toMiddleware(const kpsr::vision_ocv::ImageData &event, sensor_msgs::Image &message)
    {
        std_msgs::Header header;
        header.seq = event.seq;
        header.stamp = ros::Time::now();
        header.frame_id = event.frameId;

        char encoding[20];
        kpsr::vision_ocv::ros_mdlw::ImageEncodingHelper::cvTypeToRosImageEncoding(event.img.type(),
                                                                                  encoding);

        cv_bridge::CvImage cvImage;
        cvImage.header = header;
        cvImage.encoding = encoding;
        cvImage.image = event.img;
        message = *cvImage.toImageMsg().get();
    }

    /**
     * @brief fromMiddleware
     * @param message
     * @param event
     */
    void fromMiddleware(const sensor_msgs::Image &message, kpsr::vision_ocv::ImageData &event)
    {
        event.frameId = message.header.frame_id;
        event.seq = message.header.seq;

        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch());
        event.timestamp = ms.count();

        cv_bridge::CvImagePtr cvPtr;
        //spdlog::info("ImageFromROS received %i{}", message.header.seq);
        try {
            cvPtr = cv_bridge::toCvCopy(message, message.encoding);
        } catch (cv_bridge::Exception &e) {
            spdlog::error("ImageFromROS received. cv_bridge exception: %s", e.what());
        }

        //spdlog::info("ImageFromROS received. Converting encoding: {}", message.encoding);
        event.img = cvPtr->image;
    }
};
} // namespace kpsr
#endif
