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


set(PROJ_NAME kpsr_dds_${PROJ_MAIN_NAME})
project(${PROJ_NAME})

include(MacroConnext)

file(REMOVE_RECURSE ${CMAKE_CURRENT_SOURCE_DIR}/gen)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/gen)

file(GLOB idls "./idl/*.idl")
foreach(idl ${idls})
    connext_idlgen(${idl} ${CMAKE_CURRENT_SOURCE_DIR})
    get_filename_component(nfile ${idl} NAME)
    connext_gendatamodel(${nfile} ${CMAKE_CURRENT_SOURCE_DIR})
endforeach(idl)

# Source
# ---------------------------------------------------#
file(GLOB ${PROJ_NAME}_SRC "src/*.cpp")
file(GLOB_RECURSE ${PROJ_NAME}_HEADERS "include/*.h")
file(GLOB ${PROJ_NAME}_GEN_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/gen/*.h*")

file(GLOB_RECURSE ${PROJ_NAME}_KPSR_GEN_HEADERS
     "${CMAKE_CURRENT_SOURCE_DIR}/gen/dds/include/*.h")

# Create Library
# ---------------------------------------------------#
add_library(
    kpsr_dds_${PROJ_MAIN_NAME}_datamodel SHARED
    ${Connext_DATAMODEL} ${${PROJ_NAME}_HEADERS} ${${PROJ_NAME}_SRC}
    ${${PROJ_NAME}_GEN_HEADERS} ${${PROJ_NAME}_KPSR_GEN_HEADERS})

# Link libraries with Project
# ---------------------------------------------------#
# TARGET_LINK_LIBRARIES(${PROJ_NAME})
target_link_libraries(kpsr_dds_${PROJ_MAIN_NAME}_datamodel
                      PUBLIC RTIConnextDDS::cpp2_api kpsr_geometry)

target_include_directories(
    kpsr_dds_${PROJ_MAIN_NAME}_datamodel
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/gen>
        $<INSTALL_INTERFACE:include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/klepsydra/gen_dds_${PROJ_MAIN_NAME}>
)

set_target_properties(
    kpsr_dds_${PROJ_MAIN_NAME}_datamodel
    PROPERTIES VERSION ${KLEPSYDRA_ROBOTICS_VERSION}
               SOVERSION ${KLEPSYDRA_ROBOTICS_VERSION_MAJOR})

# Install
# ---------------------------------------------------#
install(
    TARGETS kpsr_dds_${PROJ_MAIN_NAME}_datamodel
    EXPORT KlepsydraRoboticsTargets
    DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    COMPONENT libs)
install(
    DIRECTORY "include/klepsydra"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT dev)
install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/gen/"
    DESTINATION
        "${CMAKE_INSTALL_INCLUDEDIR}/klepsydra/gen_dds_${PROJ_MAIN_NAME}"
    COMPONENT dev
    FILES_MATCHING
    PATTERN "*.h*")

add_dds_export_target(kpsr_dds_${PROJ_MAIN_NAME}_datamodel)

add_include_dirs(
    "${CMAKE_INSTALL_FULL_INCLUDEDIR}/klepsydra/gen_dds_${PROJ_MAIN_NAME}")

# PRINTBASICINFO(${PROJ_NAME})
