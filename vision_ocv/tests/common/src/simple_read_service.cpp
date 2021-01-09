#include <simple_read_service.h>
#include <opencv2/highgui/highgui.hpp>

#include <spdlog/spdlog.h>

kpsr::vision_ocv::SimpleReadService::SimpleReadService(kpsr::Environment * environment, kpsr::Subscriber<kpsr::vision_ocv::ImageData> * subscriber)
    : kpsr::Service(environment, "SimpleReadService")
    , _subscriber(subscriber)
{}

void kpsr::vision_ocv::SimpleReadService::start() {
    std::function<void(kpsr::vision_ocv::ImageData)> simpleListener = std::bind(&SimpleReadService::onEventReceived, this, std::placeholders::_1);
    this->_subscriber->registerListener("SimpleReadService", simpleListener);
}

void kpsr::vision_ocv::SimpleReadService::stop() {
    this->_subscriber->removeListener("SimpleReadService");
}


void kpsr::vision_ocv::SimpleReadService::onEventReceived(const kpsr::vision_ocv::ImageData & event) {
    spdlog::info("SimpleReadService. event received. {}"
                 ". image type: {}"
                 ". image rows: {}"
                 ". image cols: {}",
                 event.seq,
                 event.img.type(),
                 event.img.rows,
                 event.img.cols
                 );
    lastReadImg = event;
    receivedImage = true;
}

