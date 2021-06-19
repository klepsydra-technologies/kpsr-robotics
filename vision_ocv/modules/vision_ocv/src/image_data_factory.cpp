#include <klepsydra/vision_ocv/image_data_factory.h>

kpsr::vision_ocv::ImageDataFactory::ImageDataFactory(int rows, int cols, int type, const std::string& frameId)
    : _rows(rows)
    , _cols(cols)
    , _type(type)
    , _frameId(frameId)
    , creatorFunction(std::bind(&ImageDataFactory::creator, this))
    , initializerFunction(std::bind(&ImageDataFactory::initializer, this, std::placeholders::_1))
    , eventClonerFunction(std::bind(&ImageDataFactory::eventCloner, this, std::placeholders::_1, std::placeholders::_2))
{}

std::unique_ptr<kpsr::vision_ocv::ImageData> kpsr::vision_ocv::ImageDataFactory::creator() {
    std::unique_ptr<kpsr::vision_ocv::ImageData> imageEvent(new kpsr::vision_ocv::ImageData());
    imageEvent->frameId = _frameId;
    imageEvent->img.create(_rows, _cols, _type);
    return imageEvent;
}

void kpsr::vision_ocv::ImageDataFactory::initializer(kpsr::vision_ocv::ImageData & imageEvent) {
    imageEvent.frameId = _frameId;
    imageEvent.img.create(_rows, _cols, _type);
}

void kpsr::vision_ocv::ImageDataFactory::eventCloner(const kpsr::vision_ocv::ImageData & source, kpsr::vision_ocv::ImageData & target) {
    assert(target.img.type() == source.img.type());
    assert(target.frameId == source.frameId);

    // Only these three elements should have changed.
    target.seq = source.seq;
    target.timestamp = source.timestamp;
    source.img.copyTo(target.img);
}
