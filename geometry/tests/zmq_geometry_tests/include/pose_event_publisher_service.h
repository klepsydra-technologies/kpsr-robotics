/****************************************************************************
*
*                           Klepsydra Core Modules
*              Copyright (C) 2019-2020  Klepsydra Technologies GmbH
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

#ifndef POSE_EVENT_DATA_PUBLISHER_SERVICE_H
#define POSE_EVENT_DATA_PUBLISHER_SERVICE_H

#include <klepsydra/core/service.h>
#include <klepsydra/core/publisher.h>
#include <klepsydra/geometry/pose_event_data.h>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

#include <random>

const float angle_min = -3.14;
const float angle_max = 3.14;
const float range = 0.01;
const float intensity = 0.02;

class PoseEventDataPublisherService : public kpsr::Service {
public:
    PoseEventDataPublisherService(kpsr::Environment * environment, kpsr::Publisher<kpsr::geometry::PoseEventData> * publisher) :
        kpsr::Service(environment, "poseEventData_service"), _publisher(publisher) {

        // Initialize random number generation with a seed
        std::random_device rd;
        mt = new std::mt19937(rd());
        dist = new std::uniform_real_distribution<double>(-1.0, 1.0);
    }

    void start() {}
    void stop() {}

    void execute() {
        spdlog::info("PoseEventDataPublisherService.runOnce");
        sensor.seq = _seq++;
        sensor.frameId = "BODY_FRAME";
        sensor.x = 10;
        sensor.y = 50;
        sensor.z = 150;

        sensor.eulerAvailable = true;
        sensor.roll = -3.14;
        sensor.pitch = 3.14;
        sensor.yaw = 3.14;

        sensor.posCovarianceAvailable = true;
        sensor.positionCovariance.resize(3);
        sensor.positionCovariance[0] = (((*dist)(*mt)*range));
        sensor.positionCovariance[1] = (((*dist)(*mt)*range));
        sensor.positionCovariance[2] = (((*dist)(*mt)*range));
        _publisher->publish(sensor);
    }

    kpsr::geometry::PoseEventData sensor;

private:
    int _seq = 0;

    std::mt19937 * mt;
    std::uniform_real_distribution<double> * dist;

    kpsr::Publisher<kpsr::geometry::PoseEventData> * _publisher;
};

#endif // POSE_EVENT_DATA_PUBLISHER_SERVICE_H
