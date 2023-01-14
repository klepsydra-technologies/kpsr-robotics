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
void serialize(Archive &archive, kpsr::vision_ocv::ImageData &event)
{
    archive(CEREAL_NVP(event.frameId),
            CEREAL_NVP(event.seq),
            CEREAL_NVP(event.timestamp),
            CEREAL_NVP(event.img));
}

template<class Archive>
void save(Archive &ar, const cv::Mat &mat)
{
    int rows, cols, type;
    bool continuous;

    rows = mat.rows;
    cols = mat.cols;
    type = mat.type();
    continuous = mat.isContinuous();

    ar &rows &cols &type &continuous;

    if (continuous) {
        const int data_size = rows * cols * static_cast<int>(mat.elemSize());
        auto mat_data = cereal::binary_data(mat.ptr(), data_size);
        ar &mat_data;
    } else {
        const int row_size = cols * static_cast<int>(mat.elemSize());
        for (int i = 0; i < rows; i++) {
            auto row_data = cereal::binary_data(mat.ptr(i), row_size);
            ar &row_data;
        }
    }
}

template<class Archive>
void load(Archive &ar, cv::Mat &mat)
{
    int rows, cols, type;
    bool continuous;

    ar &rows &cols &type &continuous;

    if (continuous) {
        mat.create(rows, cols, type);
        const int data_size = rows * cols * static_cast<int>(mat.elemSize());
        auto mat_data = cereal::binary_data(mat.ptr(), data_size);
        ar &mat_data;
    } else {
        mat.create(rows, cols, type);
        const int row_size = cols * static_cast<int>(mat.elemSize());
        for (int i = 0; i < rows; i++) {
            auto row_data = cereal::binary_data(mat.ptr(i), row_size);
            ar &row_data;
        }
    }
}
} // namespace cereal
#endif // IMAGE_DATA_ZMQ_MAPPER_H
