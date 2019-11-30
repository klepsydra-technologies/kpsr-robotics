#ifndef SIMPLE_WRITE_SERVICE_H
#define SIMPLE_WRITE_SERVICE_H

#include <opencv2/opencv.hpp>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

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
            spdlog::info("Read a list of {} images in folder: {}", sz-2, _imageDirname);
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

        spdlog::info("SimpleWriteService::execute. imageEvent.img.type() = ", imageEvent.img.type());
        spdlog::info("SimpleWriteService::execute. fullScaleImage.type() = ", fullScaleImage.type());
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
                spdlog::info("Could not open or find the image in{}", image_path);
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
