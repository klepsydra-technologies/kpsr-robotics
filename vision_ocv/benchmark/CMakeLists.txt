# Copyright 2023 Klepsydra Technologies AG
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

set(PROJ_MAIN_NAME "robotics_benchmark")
project(${PROJ_MAIN_NAME})

find_package(OpenCV REQUIRED)
find_package(benchmark REQUIRED)

configure_file(
    "${CMAKE_SOURCE_DIR}/vision_ocv/tests/common/config.h.in"
    "${CMAKE_SOURCE_DIR}/vision_ocv/benchmark/modules/include/config.h")

# ##############################################################################
# ADD SUB FOLDERS
# ##############################################################################
add_subdirectory(modules)
