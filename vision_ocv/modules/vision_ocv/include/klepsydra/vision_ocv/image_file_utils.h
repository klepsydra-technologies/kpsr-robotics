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

#ifndef IMAGE_FILE_UTILS_H
#define IMAGE_FILE_UTILS_H

#include <string>
#include <vector>

namespace kpsr {
namespace vision_ocv {
/**
 * @brief The ImageFileUtils class
 *
 * @details This class reads all images in a folder and provide names back in the passed reference vector.
 */
class ImageFileUtils
{
public:
    /**
       * @brief getSortedListOfFilesInDir
       * @param dirName
       * @param fileNameList
       */
    static void getSortedListOfFilesInDir(const std::string &dirName,
                                          std::vector<std::string> &fileNameList);
};
} // namespace vision_ocv
} // namespace kpsr

#endif
