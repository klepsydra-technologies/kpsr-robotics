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

set(PROJ_NAME kpsr_zmq_${PROJ_MAIN_NAME})
project(${PROJ_NAME})

# find cppzmq wrapper, installed by make of cppzmq
find_package(cppzmq)

# Source
# ---------------------------------------------------#
file(GLOB ${PROJ_NAME}_SRC "src/*.cpp")
file(GLOB_RECURSE ${PROJ_NAME}_HEADERS "include/*.h")

# Create Library
# ---------------------------------------------------#
add_library(${PROJ_NAME} INTERFACE)

# Link libraries with Project
# ---------------------------------------------------#
target_link_libraries(${PROJ_NAME} INTERFACE kpsr_${PROJ_MAIN_NAME} cppzmq)
target_include_directories(
    ${PROJ_NAME}
    INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
              $<INSTALL_INTERFACE:include>)

# Install
# ---------------------------------------------------#
install(
    TARGETS ${PROJ_NAME}
    EXPORT KlepsydraRoboticsTargets
    PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT libs)

install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/klepsydra"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT dev)

add_zmq_export_target(${PROJ_NAME})

# PRINTBASICINFO(${PROJ_NAME})
