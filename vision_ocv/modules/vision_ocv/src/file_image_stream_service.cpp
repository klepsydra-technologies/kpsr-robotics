#include <klepsydra/vision_ocv/file_image_stream_service.h>

#include <spdlog/spdlog.h>

#include <klepsydra/vision_ocv/image_file_utils.h>

kpsr::vision_ocv::FileImageStreamingService::FileImageStreamingService(kpsr::Environment * environment,
                                                                       kpsr::Publisher<kpsr::vision_ocv::ImageData> * publisher,
                                                                       std::string imageDirname,
                                                                       bool restartIfNoMoreImages,
                                                                       int width,
                                                                       int height,
                                                                       std::string frameId)
    : kpsr::Service(environment, "FileImageStreamingService")
    , _publisher(publisher)
    , _imageDirname(imageDirname)
    , _restartIfNoMoreImages(restartIfNoMoreImages)
    , _readMode(cv::IMREAD_UNCHANGED)
    , _frameId(frameId)
{
    _postProcessing = [width, height](const cv::Mat & src, cv::Mat & dest) {
        resize(src, dest, cvSize(width, height));
    };
}

kpsr::vision_ocv::FileImageStreamingService::FileImageStreamingService(kpsr::Environment * environment,
                                                                       kpsr::Publisher<kpsr::vision_ocv::ImageData> * publisher,
                                                                       std::string imageDirname,
                                                                       bool restartIfNoMoreImages,
                                                                       cv::ImreadModes readMode,
                                                                       std::function<void(const cv::Mat &, cv::Mat &)> postProcessing,
                                                                       std::string frameId)
    : kpsr::Service(environment, "FileImageStreamingService")
    , _publisher(publisher)
    , _imageDirname(imageDirname)
    , _restartIfNoMoreImages(restartIfNoMoreImages)
    , _readMode(readMode)
    , _postProcessing(postProcessing)
    , _frameId(frameId)
{}

void kpsr::vision_ocv::FileImageStreamingService::start() {
    if (fileNameList.empty()) {
        index = 2;
        kpsr::vision_ocv::ImageFileUtils::getSortedListOfFilesInDir(_imageDirname, fileNameList);
        sz = fileNameList.size();
        spdlog::info("Read a list of {} images in folder: {}", sz-2, _imageDirname);
    }
}

void kpsr::vision_ocv::FileImageStreamingService::stop() {
    fileNameList.clear();
}

void kpsr::vision_ocv::FileImageStreamingService::execute() {
    imageEvent.frameId = _frameId;
    bool gotImage = getImage(_fileImage);

    if (gotImage) {
        _postProcessing(_fileImage, imageEvent.img);

        spdlog::debug("FileImageStreamingService::execute. imageEvent.img.type() = {}", imageEvent.img.type());
        spdlog::debug("FileImageStreamingService::execute. fullScaleImage.type() = {}", _fileImage.type());

        imageEvent.seq = publishedEvents++;
        _publisher->publish(imageEvent);
    } else {
        this->shutdown();
    }
}

bool kpsr::vision_ocv::FileImageStreamingService::hasMoreImages() {
    return (index < (sz));
}

bool kpsr::vision_ocv::FileImageStreamingService::getImage(cv::Mat & image) {
    if (hasMoreImages()) {
        std::string image_path;
        image_path.append(_imageDirname);
        image_path.append("/");
        image_path.append(fileNameList[index++]);
        image = cv::imread(image_path, _readMode);

        if(!image.data) {
            spdlog::info("Could not open or find the image in {}", image_path);
            return false;
        }
        return true;
    }
    else
    {
        if (_restartIfNoMoreImages) {
            this->shutdown();
            this->startup();
            return getImage(image);
        }
        return false;
    }
}
