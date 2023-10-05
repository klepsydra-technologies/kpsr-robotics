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

#ifndef FILE_IMG_STREAM__SERVICE_H
#define FILE_IMG_STREAM__SERVICE_H

#include <opencv2/opencv.hpp>

#include <klepsydra/sdk/publisher.h>
#include <klepsydra/sdk/service.h>

#include <klepsydra/vision_ocv/image_event_data.h>

namespace kpsr {
namespace vision_ocv {
class FileImageStreamingService : public kpsr::Service
{
public:
    FileImageStreamingService(kpsr::Environment *environment,
                              kpsr::Publisher<kpsr::vision_ocv::ImageData> *publisher,
                              const std::string &imageDirname,
                              bool restartIfNoMoreImages,
                              int width = 480,
                              int height = 320,
                              const std::string &frameId = "body",
                              const std::string &serviceName = "FileImageStreamingService");

    FileImageStreamingService(kpsr::Environment *environment,
                              kpsr::Publisher<kpsr::vision_ocv::ImageData> *publisher,
                              const std::string &imageDirname,
                              bool restartIfNoMoreImages,
                              cv::ImreadModes readMode,
                              std::function<void(const cv::Mat &, cv::Mat &)> postProcessing,
                              const std::string &frameId = "body",
                              const std::string &serviceName = "FileImageStreamingService");

    void start();

    void stop();

    void execute();

    int publishedEvents = 0;
    cv::Mat fullScaleImage;
    kpsr::vision_ocv::ImageData imageEvent;

private:
    bool hasMoreImages();
    bool getImage(cv::Mat &image);

    kpsr::Publisher<kpsr::vision_ocv::ImageData> *_publisher;
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
} // namespace vision_ocv
} // namespace kpsr

#endif // FILE_IMG_STREAM__SERVICE_H
