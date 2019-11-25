/****************************************************************************
*
*                           Klepsydra Core Modules
*              Copyright (C) 2019-2020  Klepsydra Technologies GmbH
*                            All Rights Reserved.
*
*  This file is subject to the terms and conditions defined in
*  file ‘LICENSE.md’, which is part of this source code package.
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

#ifndef SIMPLE_WRITE_SERVICE_H
#define SIMPLE_WRITE_SERVICE_H

#include <opencv2/opencv.hpp>

#include <klepsydra/core/service.h>
#include <klepsydra/core/publisher.h>

#include <klepsydra/vision_ocv/image_event_data.h>

#include "file_utils.h"

class SimpleWriteService : public kpsr::Service
{
public:
    SimpleWriteService(kpsr::Environment * environment,
                       kpsr::Publisher<kpsr::vision_ocv::ImageData> * publisher,
                       std::string imageDirname,
                       bool restartIfNoMoreImages)
        : kpsr::Service(environment, "SimpleWriteService")
        , _publisher(publisher)
        , _imageDirname(imageDirname)
        , _restartIfNoMoreImages(restartIfNoMoreImages)
    {}

    void start() {
        if (fileNameList == nullptr) {
            index = 2;
            fileNameList = new std::vector<std::string>();
            FileUtils::getSortedListOfFilesInDir(_imageDirname, fileNameList);
            sz = fileNameList->size();
            std::cout << "Read a list of " << sz-2 << " images in folder: " << _imageDirname << std::endl;
        }
    }

    void stop() {
        fileNameList = nullptr;
    }

    void execute() {
        imageEvent.seq = publishedEvents++;
        imageEvent.frameId = "body";
        fullScaleImage = getImage();
        resize(fullScaleImage, imageEvent.img, cvSize(480, 320));

        std::cout << "SimpleWriteService::execute. imageEvent.img.type() = " << imageEvent.img.type() << std::endl;
        std::cout << "SimpleWriteService::execute. fullScaleImage.type() = " << fullScaleImage.type() << std::endl;
        _publisher->publish(imageEvent);
    }

    int publishedEvents = 0;
    cv::Mat fullScaleImage;
    kpsr::vision_ocv::ImageData imageEvent;

private:
    bool hasMoreImages() {
        return (index < (sz));
    }

    cv::Mat getImage() {
        if (hasMoreImages()) {
            std::string image_path;
            image_path.append(_imageDirname);
            image_path.append("/");
            image_path.append((*fileNameList)[index++]);
            _fileImage = cv::imread(image_path);
            if(!_fileImage.data) {
                std::cout<<"Could not open or find the image in" << image_path << std::endl ;
            }

            return _fileImage;

        }
        else
        {
            if (_restartIfNoMoreImages) {
                this->stop();
                this->start();
                return getImage();
            }
        }
    }

    kpsr::Publisher<kpsr::vision_ocv::ImageData> * _publisher;
    std::string _imageDirname;
    bool _restartIfNoMoreImages;

    cv::Mat _fileImage;
    std::vector<std::string> * fileNameList = nullptr;
    unsigned index;
    std::vector<int>::size_type sz;
};


#endif // SIMPLE_WRITE_SERVICE_H
