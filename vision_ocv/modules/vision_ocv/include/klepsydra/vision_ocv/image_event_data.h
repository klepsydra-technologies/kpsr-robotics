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

#ifndef IMAGE_DATA_H
#define IMAGE_DATA_H

#include <string>

#include <opencv2/core/core.hpp>

#include <klepsydra/core/sensor.h>

namespace kpsr {
namespace vision_ocv {
/**
 * @brief The ImageData struct
 *
 * @copyright 2023 Klepsydra Technologies AG
 *
 * @version 2.0.1
 *
 * @ingroup kpsr-vision-application
 *
 * @details Base image structure event data. Should be ROS and OpenCV compatible
 */
struct ImageData : public Sensor
{
public:
    /**
     * @brief ImageData
     */
    ImageData() {}

    /**
     * @brief ImageData
     * @param frameId
     * @param seq
     * @param img
     */
    ImageData(const std::string &frameId, int seq, cv::Mat img)
        : Sensor(frameId, seq)
        , img(img)
    {}

    /**
     * @brief ImageData
     * @param that
     */
    ImageData(const ImageData &that)
        : Sensor(that)
        , img(that.img)
    {}

    /**
     * @brief clone
     * @param that
     */
    void clone(const ImageData &that)
    {
        Sensor::clone(that);
        that.img.copyTo(img);
    }

    /**
     * @brief img
     */
    cv::Mat img;
};
} // namespace vision_ocv
} // namespace kpsr
#endif
