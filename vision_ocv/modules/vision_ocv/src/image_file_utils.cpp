// Copyright 2023 Klepsydra Technologies AG
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <algorithm>
#include <dirent.h>
#include <sys/types.h>

#include <klepsydra/vision_ocv/image_file_utils.h>

void kpsr::vision_ocv::ImageFileUtils::getSortedListOfFilesInDir(
    const std::string &dirName, std::vector<std::string> &fileNameList)
{
    dirent *de;
    DIR *dp;
    errno = 0;
    dp = opendir(dirName.c_str());
    if (dp) {
        while (true) {
            errno = 0;
            de = readdir(dp);
            if (de == nullptr)
                break;
            fileNameList.push_back(std::string(de->d_name));
        }
        closedir(dp);
        std::sort(fileNameList.begin(), fileNameList.end());
    }
}
