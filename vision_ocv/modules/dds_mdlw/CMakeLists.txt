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

SET(PROJ_NAME kpsr_dds_${PROJ_MAIN_NAME})
PROJECT(${PROJ_NAME})

include (MacroConnext)
find_package (Connext REQUIRED)
SET (DEFINITIONS ${DEFINITIONS} " -DDDS_IMPLEMENTATION_${DDS_IMPLEMENTATION}")

add_definitions (
  ${Connext_DEFINITIONS}
  ${DEFINITIONS}
)

file(REMOVE_RECURSE ${CMAKE_CURRENT_SOURCE_DIR}/gen)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/gen)

file(GLOB idls "./idl/*.idl")
FOREACH(idl ${idls})
        Connext_IDLGEN (${idl} ${CMAKE_CURRENT_SOURCE_DIR})
        GET_FILENAME_COMPONENT(nfile ${idl} NAME)
        Connext_GENDATAMODEL(${nfile} ${CMAKE_CURRENT_SOURCE_DIR})
ENDFOREACH(idl)

# Source
#---------------------------------------------------#
FILE(GLOB ${PROJ_NAME}_SRC
    "src/*.cpp"
)
FILE(GLOB_RECURSE ${PROJ_NAME}_HEADERS
    "include/*.h"
)
FILE(GLOB ${PROJ_NAME}_GEN_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/gen/*.h*"
)

FILE(GLOB_RECURSE ${PROJ_NAME}_KPSR_GEN_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/gen/dds/include/*.h"
)

# Create Library
#---------------------------------------------------#
ADD_LIBRARY (kpsr_dds_${PROJ_MAIN_NAME}_datamodel SHARED ${Connext_DATAMODEL} ${${PROJ_NAME}_HEADERS} ${${PROJ_NAME}_SRC} ${${PROJ_NAME}_GEN_HEADERS} ${${PROJ_NAME}_KPSR_GEN_HEADERS})

# Link libraries with Project
#---------------------------------------------------#
TARGET_LINK_LIBRARIES(kpsr_dds_${PROJ_MAIN_NAME}_datamodel ${Connext_LIBRARIES} kpsr_${PROJ_MAIN_NAME})

TARGET_INCLUDE_DIRECTORIES(kpsr_dds_${PROJ_MAIN_NAME}_datamodel
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/gen>
  $<INSTALL_INTERFACE:include>
  ${Connext_INCLUDE_DIRS}
  )

# Install
#---------------------------------------------------#
INSTALL(TARGETS kpsr_dds_${PROJ_MAIN_NAME}_datamodel
    EXPORT KlepsydraRoboticsTargets
    DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    COMPONENT libs
)
INSTALL(DIRECTORY "include/klepsydra"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT dev
)
INSTALL(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/gen/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/klepsydra/gen_dds_${PROJ_MAIN_NAME}"
    FILES_MATCHING PATTERN "*.h*"
    COMPONENT dev
)

add_dds_export_target(kpsr_dds_${PROJ_MAIN_NAME}_datamodel)

add_include_dirs("${CMAKE_INSTALL_FULL_INCLUDEDIR}/klepsydra/gen_dds_${PROJ_MAIN_NAME}")

#PRINTBASICINFO(${PROJ_NAME})

