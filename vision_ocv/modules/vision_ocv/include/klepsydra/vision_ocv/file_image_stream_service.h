/****************************************************************************
*
*                           Klepsydra Core Modules
*              Copyright (C) 2020-2022  Klepsydra Technologies GmbH
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

#ifndef FILE_IMG_STREAM__SERVICE_H
#define FILE_IMG_STREAM__SERVICE_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc_c.h>

#include <klepsydra/core/service.h>
#include <klepsydra/core/publisher.h>

#include <klepsydra/vision_ocv/image_event_data.h>

namespace kpsr {
namespace vision_ocv {
class FileImageStreamingService : public kpsr::Service
{
public:
    FileImageStreamingService(kpsr::Environment * environment,
                              kpsr::Publisher<kpsr::vision_ocv::ImageData> * publisher,
                              std::string imageDirname,
                              bool restartIfNoMoreImages,
                              int width = 480,
                              int height = 320,
                              std::string frameId = "body");

    FileImageStreamingService(kpsr::Environment * environment,
                              kpsr::Publisher<kpsr::vision_ocv::ImageData> * publisher,
                              std::string imageDirname,
                              bool restartIfNoMoreImages,
                              cv::ImreadModes readMode,
                              std::function<void(const cv::Mat &, cv::Mat &)> postProcessing,
                              std::string frameId = "body");

    void start();

    void stop();

    void execute();

    int publishedEvents = 0;
    cv::Mat fullScaleImage;
    kpsr::vision_ocv::ImageData imageEvent;

private:
    bool hasMoreImages();
    bool getImage(cv::Mat & image);

    kpsr::Publisher<kpsr::vision_ocv::ImageData> * _publisher;
    std::string _imageDirname;
    bool _restartIfNoMoreImages;

    cv::ImreadModes _readMode;
    std::function<void(const cv::Mat &, cv::Mat &)> _postProcessing;
    cv::Mat _fileImage;
    std::vector<std::string> fileNameList;
    unsigned index;
    std::vector<int>::size_type sz;
    int _width;
    int _height;
    std::string _frameId;
};
}
}

#endif // FILE_IMG_STREAM__SERVICE_H
