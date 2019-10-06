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

#ifndef POSE_EVENT_DATA_PUBLISHER_SERVICE_H
#define POSE_EVENT_DATA_PUBLISHER_SERVICE_H

#include <klepsydra/core/service.h>
#include <klepsydra/core/publisher.h>
#include <klepsydra/geometry/pose_event_data.h>

#include <iostream>
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
        std::cout << "PoseEventDataPublisherService.runOnce" << std::endl;
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
