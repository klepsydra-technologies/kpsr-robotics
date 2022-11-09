#****************************************************************************
#
#                           Klepsydra Core Modules
#              Copyright (C) 2019-2020  Klepsydra Technologies GmbH
#                            All Rights Reserved.
#
#  This file is subject to the terms and conditions defined in
#  file 'LICENSE.md', which is part of this source code package.
#
#  NOTICE:  All information contained herein is, and remains the property of Klepsydra
#  Technologies GmbH and its suppliers, if any. The intellectual and technical concepts
#  contained herein are proprietary to Klepsydra Technologies GmbH and its suppliers and
#  may be covered by Swiss and Foreign Patents, patents in process, and are protected by
#  trade secret or copyright law. Dissemination of this information or reproduction of
#  this material is strictly forbidden unless prior written permission is obtained from
#  Klepsydra Technologies GmbH.
#
#****************************************************************************

set(PROJ_NAME kpsr_zmq_${PROJ_MAIN_NAME}_tests)
project(${PROJ_NAME})

# find cppzmq wrapper, installed by make of cppzmq
find_package(cppzmq)
# Include directories with headers
# ---------------------------------------------------#
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(
    ${CMAKE_SOURCE_DIR}/${PROJ_MAIN_NAME}/modules/${PROJ_MAIN_NAME}/include)
include_directories(
    ${CMAKE_SOURCE_DIR}/${PROJ_MAIN_NAME}/modules/zmq_mdlw/include)
include_directories(${cppzmq_INCLUDE_DIR})
include_directories(${KLEPSYDRA_INCLUDE_DIRS})

# Source
# ---------------------------------------------------#
file(GLOB ${PROJ_NAME}_SRC "src/*.cpp")
file(GLOB ${PROJ_NAME}_HEADERS "include/*.h")

# Link libraries with Project
# ---------------------------------------------------#
link_directories(${KPSR_LIBRARY_PATH})
add_executable(${PROJ_NAME} ${${PROJ_NAME}_HEADERS} ${${PROJ_NAME}_SRC})

# ---------------------------------------------------#
target_link_libraries(${PROJ_NAME} ${KLEPSYDRA_CORE_LIBRARIES} cppzmq
                      gtest_main atomic)

add_test(NAME ${PROJ_NAME} COMMAND ${PROJ_NAME})
