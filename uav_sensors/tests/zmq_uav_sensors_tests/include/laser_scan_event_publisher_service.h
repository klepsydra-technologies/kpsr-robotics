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

#ifndef LASER_SCAN_EVENT_PUBLISHER_SERVICE_H
#define LASER_SCAN_EVENT_PUBLISHER_SERVICE_H

#include <random>

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"

#include <klepsydra/sdk/publisher.h>
#include <klepsydra/sdk/service.h>

#include <klepsydra/sensors/laser_scan_event.h>

const float angle_min = -3.14f;
const float angle_max = 3.14f;
const float range = 0.01f;
const float intensity = 0.02f;

class LaserScanEventPublisherService : public kpsr::Service
{
public:
    LaserScanEventPublisherService(kpsr::Environment *environment,
                                   kpsr::Publisher<kpsr::sensors::LaserScanEvent> *publisher)
        : kpsr::Service(nullptr, environment, "laserScanEvent_service")
        , _publisher(publisher)
    {
        // Initialize random number generation with a seed
        std::random_device rd;
        mt = new std::mt19937(rd());
        dist = new std::uniform_real_distribution<double>(-1.0, 1.0);
    }

    void start() {}
    void stop() {}

    void execute()
    {
        spdlog::info("LaserScanEventPublisherService.runOnce");
        sensor.seq = _seq++;
        sensor.frameId = "BODY_FRAME";
        sensor.angle_min = -3.14f;
        sensor.angle_max = 3.14f;
        sensor.angle_increment = 3.14f;
        sensor.range_min = 10;
        sensor.range_max = 50;
        sensor.scan_time = 1.0;

        sensor.ranges.resize(3);
        sensor.ranges[0] = (((*dist)(*mt) * range));
        sensor.ranges[1] = (((*dist)(*mt) * range));
        sensor.ranges[2] = (((*dist)(*mt) * range));
        sensor.intensities.resize(3);
        sensor.intensities[0] = (((*dist)(*mt) * intensity));
        sensor.intensities[1] = (((*dist)(*mt) * intensity));
        sensor.intensities[2] = (((*dist)(*mt) * intensity));

        spdlog::info("LaserScanEventPublisherService.runOnce. seq: {}"
                     ". sensor.frameId: {}"
                     ". sensor.angle_min: {}"
                     ". sensor.range_min: {}"
                     ". sensor.ranges.size(): {}"
                     ". sensor.ranges[0]: {}"
                     ". sensor.intensities.size(): {}"
                     ". sensor.intensities[0]: {}",
                     sensor.seq,
                     sensor.frameId,
                     sensor.angle_min,
                     sensor.range_min,
                     sensor.ranges.size(),
                     sensor.ranges[0],
                     sensor.intensities.size(),
                     sensor.intensities[0]);
        _publisher->publish(sensor);
    }

    kpsr::sensors::LaserScanEvent sensor;

private:
    int _seq = 0;

    std::mt19937 *mt;
    std::uniform_real_distribution<double> *dist;

    kpsr::Publisher<kpsr::sensors::LaserScanEvent> *_publisher;
};

#endif // LASER_SCAN_EVENT_PUBLISHER_SERVICE_H
