/**
 *                               Klepsydra Toolset
 *
 *   This software and documentation are Copyright 2016 to 2017 Klepsydra Robotics
 *   Limited and its licensees. All rights reserved. See file:
 *
 *                               LICENSE.md
 *
 *   for full copyright notice and license terms.
 *
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
 * @copyright Klepsydra Robotics 2017-2018.
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
        img = that.img;
    }

    /**
     * @brief img
     */
    cv::Mat img;
};
} // namespace vision_ocv
} // namespace kpsr
#endif
