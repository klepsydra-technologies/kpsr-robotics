/****************************************************************************
*
*                           Klepsydra Core Modules
*              Copyright (C) 2019-2020  Klepsydra Technologies GmbH
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*****************************************************************************/
#include <thread>

#include <klepsydra/mem_vision_ocv/image_multiplexer_vision_ocv_provider.h>

#include "simple_write_service.h"
#include "simple_read_service.h"
#include "slow_read_service.h"

#include "gtest/gtest.h"

#include "config.h"

TEST(HPVisionTest, HPVisionTest) {
    kpsr::vision_ocv::high_performance::ImageMultiplexerVisionMiddlewareProvider<128> provider(nullptr, "test", 1080, 2040, 16, "body");

    //std::cout << "Creating services." << std::endl;
    kpsr::Publisher<kpsr::vision_ocv::ImageData> * publisher = provider.underlying->getPublisher();
    SimpleWriteService writeService(nullptr, publisher, TEST_DATA, true);

    kpsr::Subscriber<kpsr::vision_ocv::ImageData> * subscriber = provider.underlying->getSubscriber();
    SimpleReadService simpleReadService(nullptr, subscriber);
    SlowReadService slowReadService(nullptr, subscriber);

    std::chrono::milliseconds ms1 = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
    long before = ms1.count();

    //std::cout << "Starting services." << std::endl;
    writeService.start();
    simpleReadService.start();
    slowReadService.start();

    // Publish some integers.
    for (int i = 0; i < 50; i++) {
        //std::cout << "Executing services." << std::endl;
        writeService.execute();
        simpleReadService.execute();
        slowReadService.execute();
    }

    writeService.stop();
    simpleReadService.stop();
    slowReadService.stop();

    ASSERT_EQ(writeService.publishedEvents, 50);
    ASSERT_EQ(simpleReadService.receivedEvents, 50);
    ASSERT_EQ(slowReadService.receivedEvents, 50);
}

