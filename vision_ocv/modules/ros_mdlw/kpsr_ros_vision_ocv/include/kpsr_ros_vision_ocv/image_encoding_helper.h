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

#ifndef IMAGE_ENCODING_HELPER_H
#define IMAGE_ENCODING_HELPER_H

namespace kpsr {
namespace vision_ocv {
namespace ros_mdlw {
/**
 * @brief The ImageEncodingHelper class
 *
 * @copyright 2023 Klepsydra Technologies AG
 *
 * @version 2.1.0
 *
 * @ingroup kpsr-vision-ros_mdlw-internal
 *
 */
class ImageEncodingHelper
{
public:
    static int cvTypeFromRosImageEncoding(const char *rosImgEncoding);

    /**
     * @brief cvTypeToRosImageEncoding
     * @param cvType
     * @param rosImageEncoding
     */
    static void cvTypeToRosImageEncoding(int cvType, char *rosImageEncoding);
};
} // namespace ros_mdlw
} // namespace vision_ocv
} // namespace kpsr
#endif
