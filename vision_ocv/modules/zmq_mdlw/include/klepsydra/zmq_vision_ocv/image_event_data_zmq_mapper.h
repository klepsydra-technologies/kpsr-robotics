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

#ifndef IMAGE_DATA_ZMQ_MAPPER_H
#define IMAGE_DATA_ZMQ_MAPPER_H

#include <streambuf>

#include <cereal/cereal.hpp>
#include <cereal/types/string.hpp>

#include <klepsydra/vision_ocv/image_event_data.h>

namespace cereal {

template<class Archive>
/**
 * @brief serialize
 * @param archive
 * @param event
 */
void serialize(Archive & archive, kpsr::vision_ocv::ImageData & event)
{
    archive( CEREAL_NVP(event.frameId),
             CEREAL_NVP(event.seq),
             CEREAL_NVP(event.timestamp),
             CEREAL_NVP(event.img) );
}

template<class Archive>
void save(Archive& ar, const cv::Mat& mat)
{
    int rows, cols, type;
    bool continuous;

    rows = mat.rows;
    cols = mat.cols;
    type = mat.type();
    continuous = mat.isContinuous();

    ar & rows & cols & type & continuous;

    if (continuous) {
        const int data_size = rows * cols * static_cast<int>(mat.elemSize());
        auto mat_data = cereal::binary_data(mat.ptr(), data_size);
        ar & mat_data;
    }
    else {
        const int row_size = cols * static_cast<int>(mat.elemSize());
        for (int i = 0; i < rows; i++) {
            auto row_data = cereal::binary_data(mat.ptr(i), row_size);
            ar & row_data;
        }
    }
}

template<class Archive>
void load(Archive& ar, cv::Mat& mat)
{
    int rows, cols, type;
    bool continuous;

    ar & rows & cols & type & continuous;

    if (continuous) {
        mat.create(rows, cols, type);
        const int data_size = rows * cols * static_cast<int>(mat.elemSize());
        auto mat_data = cereal::binary_data(mat.ptr(), data_size);
        ar & mat_data;
    }
    else {
        mat.create(rows, cols, type);
        const int row_size = cols * static_cast<int>(mat.elemSize());
        for (int i = 0; i < rows; i++) {
            auto row_data = cereal::binary_data(mat.ptr(i), row_size);
            ar & row_data;
        }
    }
}
}
#endif // IMAGE_DATA_ZMQ_MAPPER_H
