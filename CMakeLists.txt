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

# Main header: Project name & Configuration
# ------------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.12)

set(PROJ_MAIN_NAME "klepsydra-robotics")
project(${PROJ_MAIN_NAME})

set(KPSR_ROBOTICS_MAJOR_VERSION 4)
set(KPSR_ROBOTICS_MINOR_VERSION 0)
set(KPSR_ROBOTICS_PATCH_VERSION 0)
set(KPSR_ROBOTICS_VERSION
    ${KPSR_ROBOTICS_MAJOR_VERSION}.${KPSR_ROBOTICS_MINOR_VERSION}.${KPSR_ROBOTICS_PATCH_VERSION}
)

# Configuration types
set(CMAKE_CONFIGURATION_TYPES
    "Debug;Release"
    CACHE STRING "Configs" FORCE)
if(DEFINED CMAKE_BUILD_TYPE AND CMAKE_VERSION VERSION_GREATER "2.8")
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
                                                 ${CMAKE_CONFIGURATION_TYPES})
endif()

# Install binaries
if(DEFINED THIRDPARTIES_PATH)

else()
    set(THIRDPARTIES_PATH ${CMAKE_SOURCE_DIR}/thirdparties)
endif()
message(STATUS "Thirdparties install path: " ${THIRDPARTIES_PATH})

if(DEFINED GTEST_PATH)

else()
    set(GTEST_PATH ${THIRDPARTIES_PATH}/googletest) # default google test path
endif()
message(STATUS "Google test path: " ${GTEST_PATH})
if(DEFINED KPSR_BUILD_PATH)

else()
    set(KPSR_BUILD_PATH ${CMAKE_SOURCE_DIR}/kpsr-build)
endif()
message(STATUS "kpsr-build path: " ${KPSR_BUILD_PATH})

if(DEFINED CMAKE_PREFIX_PATH)
    set(KPSR_LIBRARY_PATH ${CMAKE_PREFIX_PATH}/lib)
endif()

# Configure variables
# ------------------------------------------------------------------------------------------------------

# Paths
set(CMAKE_MODULE_PATH ${KPSR_BUILD_PATH}/cmake)
set(LIBRARY_OUTPUT_PATH
    ${PROJECT_BINARY_DIR}/bin
    CACHE PATH "Library output" FORCE)
set(EXECUTABLE_OUTPUT_PATH
    ${PROJECT_BINARY_DIR}/bin
    CACHE PATH "Executable output" FORCE)

# Must use GNUInstallDirs to install libraries into correct locations on all
# platforms.
include(GNUInstallDirs)

# Build type
set(BUILD_SHARED_LIBS
    ON
    CACHE BOOL "Build shared libraries" FORCE)

cmake_policy(SET CMP0057 NEW)
cmake_policy(SET CMP0054 NEW)
find_package(Klepsydra 8 REQUIRED)

include(CheckCXXCompilerFlag)
include(CheckIncludeFileCXX)

check_cxx_compiler_flag(-std=gnu++11 HAS_CXX11)
if(HAS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
endif()

if(NOT APPLE)
    set(CMAKE_INSTALL_RPATH $ORIGIN)
    check_cxx_compiler_flag(-Wl,--no-undefined HAS_NO_UNDEFINED)
    if(HAS_NO_UNDEFINED)
        set(CMAKE_EXE_LINKER_FLAGS
            "${CMAKE_EXE_LINKER_FLAGS} -Wl,--no-undefined")
        set(CMAKE_SHARED_LINKER_FLAGS
            "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")
        set(CMAKE_MODULE_LINKER_FLAGS
            "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")
    endif()
endif()

check_cxx_compiler_flag(-pedantic HAS_PEDANTIC)
if(HAS_PEDANTIC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
endif()

check_cxx_compiler_flag(-Wall HAS_WALL)
if(HAS_WALL)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()

check_include_file_cxx(sys/epoll.h HAS_EPOLL)
if(HAS_EPOLL)
    add_definitions(-DHAS_EPOLL)
else()
    add_definitions(-DUSE_GET_WRITE_QUEUE)
endif()

add_definitions(-std=c++11)
if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 7.0)
    add_definitions(-faligned-new)
endif()
add_definitions(-fno-strict-overflow)
add_definitions(-Wno-deprecated-declarations)
add_definitions(-Wno-comment)

option(KPSR_ENABLE_EXAMPLES "Enable building and installing examples" OFF)
option(KPSR_ENABLE_TESTS "Enable tests" ON)

if(KPSR_ENABLE_TESTS)
    enable_testing()
endif()

if(KPSR_WITH_CODE_METRICS)
    if(CMAKE_BUILD_TYPE MATCHES Debug AND CMAKE_COMPILER_IS_GNUCXX)
        include(CodeCoverage)
        set(CODE_COVERAGE_VERBOSE ON)
        append_coverage_compiler_flags()
    endif()
    # Code style check
    include(CppcheckTargets)
    include(Findcppcheck)
endif()

# Code format check
include(CodeFormat)
# CCACHE support
include(FindCcache)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include(KlepsydraBuild)

# Configuration current project
# ------------------------------------------------------------------------------------------------------

# Dependencies

find_package(Threads REQUIRED)

# Project Logic
# ------------------------------------------------------------------------------------------------------

# ##############################################################################
# ADD SUB FOLDERS
# ##############################################################################
add_subdirectory(geometry)
add_subdirectory(uav_sensors)
if(KPSR_WITH_OCV)
    add_subdirectory(vision_ocv)
    string(APPEND KPSR_PACKAGE_OPTIONS "-ocv")
endif()

# Code Coverage
if(KPSR_WITH_CODE_METRICS
   AND CMAKE_BUILD_TYPE MATCHES Debug
   AND CMAKE_COMPILER_IS_GNUCXX)
    string(REPLACE ${CMAKE_SOURCE_DIR}/ "" THIRDPARTIES_PATH_COVERAGE
                   ${THIRDPARTIES_PATH})
    list(
        APPEND
        COVERAGE_EXCLUDES
        ${THIRDPARTIES_PATH_COVERAGE}
        ${CMAKE_PREFIX_PATH}
        geometry/tests
        uav_sensors/tests
        vision_ocv/tests
        vision_ocv/benchmark)
    setup_target_for_coverage_gcovr_xml(NAME coverage EXECUTABLE make test)
endif()

if(KPSR_RUNTIME)

else()
    # add a target to generate API documentation with Doxygen
    if(KPSR_WITH_DOXYGEN)
        find_package(Doxygen REQUIRED)
        set(DOC_PROJECT_NAME "Klepsydra Core")
        set(DOC_PROJECT_BRIEF "Klepsydra Core API")

        # Generate documentation only for directories where there is a
        # group_definitions.h file

        file(GLOB_RECURSE DOC_DIRS "*/modules/group_definitions.h")
        string(REGEX REPLACE "/group_definitions.h[;]?" " " DOC_DIRS
                             "${DOC_DIRS}")
        list(APPEND DOC_DIRS ${PY_DOC_DIRS})

        configure_file(${KPSR_BUILD_PATH}/docs/Doxyfile.in
                       ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
        add_custom_target(
            doc
            ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
            COMMAND
                moxygen --templates ${KPSR_BUILD_PATH}/docs/moxygen/templates
                --groups --output api-%s.md ./xml
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
    endif(KPSR_WITH_DOXYGEN)
endif()

set(INSTALL_CMAKE_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/klepsydrarobotics)

# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
    set(var INSTALL_${p}_DIR)
    if(NOT IS_ABSOLUTE "${${var}}")
        set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
    endif()
endforeach()

list(APPEND EXPORT_INCLUDE_DIRS ${CMAKE_INSTALL_FULL_INCLUDEDIR})
export(TARGETS ${CORE_EXPORT_TARGETS} ${ZMQ_EXPORT_TARGETS}
       FILE "${PROJECT_BINARY_DIR}/KlepsydraRoboticsTargets.cmake")

# Export the package for use from the build-tree (this registers the build-tree
# with a global CMake-registry)
export(PACKAGE robotics)

# Create the KlepsydraRoboticsConfig.cmake and KlepsydraRoboticsConfigVersion
# files
configure_file(KlepsydraRoboticsConfig.cmake.in
               "${PROJECT_BINARY_DIR}/KlepsydraRoboticsConfig.cmake" @ONLY)

configure_file(
    KlepsydraRoboticsConfig.cmake.in
    "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/KlepsydraRoboticsConfig.cmake"
    @ONLY)
# ... for both
configure_file(
    KlepsydraRoboticsConfigVersion.cmake.in
    "${PROJECT_BINARY_DIR}/KlepsydraRoboticsConfigVersion.cmake" @ONLY)

# Install the KlepsydraRoboticsConfig.cmake and
# KlepsydraRoboticsConfigVersion.cmake
install(
    FILES
        "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/KlepsydraRoboticsConfig.cmake"
        "${PROJECT_BINARY_DIR}/KlepsydraRoboticsConfigVersion.cmake"
    DESTINATION "${INSTALL_CMAKE_DIR}"
    COMPONENT dev)

# Install the export set for use with the install-tree
install(
    EXPORT KlepsydraRoboticsTargets
    DESTINATION "${INSTALL_CMAKE_DIR}"
    COMPONENT dev)

# PACKAGING
if(NOT DEFINED KPSR_VERSION_MAJOR)
    set(KPSR_VERSION_MAJOR ${KPSR_ROBOTICS_MAJOR_VERSION})
endif()

if(NOT DEFINED KPSR_VERSION_MINOR)
    set(KPSR_VERSION_MINOR ${KPSR_ROBOTICS_MINOR_VERSION})
endif()

if(NOT DEFINED KPSR_VERSION_PATCH)
    set(KPSR_VERSION_PATCH ${KPSR_ROBOTICS_PATCH_VERSION})
endif()

set(KPSR_PACKAGE_DESCRIPTION "Klepsydra SDK Robotics Libraries")
set(KPSR_PACKAGE_DESCRIPTION_SUMMARY "Klepsydra SDK Robotics Libraries")

include(KlepsydraPackaging)
