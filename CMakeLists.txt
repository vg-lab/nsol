
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   NSOL - NeuroScience Ontology Library
#   2014 (c) Universidad Rey Juan Carlos
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

project(nsol)
cmake_minimum_required(VERSION 2.8)

# Version numbers
set(nsol_VERSION_MAJOR 0)
set(nsol_VERSION_MINOR 1)
set(nsol_VERSION_PATCH 0)
set(nsol_VERSION
    ${nsol_VERSION_MAJOR}.${nsol_VERSION_MINOR}.${nsol_VERSION_PATCH})

# Default build type is Debug 
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)


# Custom flags for Release and Debug
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src ${VMMLIB_INSTALL_DIR}/include) 

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Find files to install 
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
file(GLOB DEPLOY_FILES_AND_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src/*")
foreach(ITEM ${DEPLOY_FILES_AND_DIRS})
   IF( IS_DIRECTORY "${ITEM}" )
      LIST( APPEND DIRS_TO_DEPLOY "${ITEM}" )
   ELSE()
     GET_FILENAME_COMPONENT(FILE_EXT "${ITEM}" "EXT")
     IF( FILE_EXT STREQUAL ".h" )
       LIST( APPEND FILES_TO_DEPLOY "${ITEM}" )
     ENDIF()
   ENDIF()
endforeach()
INSTALL( FILES ${FILES_TO_DEPLOY} DESTINATION include/ )
INSTALL( DIRECTORY ${DIRS_TO_DEPLOY} DESTINATION include/ )
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

# Test subdirectory 
add_subdirectory(test)

#configure_file(
#${CMAKE_CURRENT_SOURCE_DIR}/src/nsol/NsolConfig.h.in
#${CMAKE_CURRENT_BINARY_DIR}/src/nsol/NsolConfig.h
#)


 
# Build library
add_library (nsol 
${CMAKE_CURRENT_SOURCE_DIR}/src/nsol/Column.cpp
)

# BBPSDK setup
set(BBPSDK_DIR "${BBPSDK_INSTALL_DIR}/share/BBPSDK/CMake")
set(Lunchbox_DIR "${BBPSDK_INSTALL_DIR}/share/Lunchbox/CMake")
set(Brion_DIR "${BBPSDK_INSTALL_DIR}/share/Brion/CMake")

find_package(BBPSDK)

if (BBPSDK_FOUND)
  message(STATUS "BBPSDK found")
  find_package(Boost 1.45.0 COMPONENTS system REQUIRED)
  INCLUDE_DIRECTORIES(${BBPSDK_INCLUDE_DIRS})
  TARGET_LINK_LIBRARIES(nsol ${BBPSDK_LIBRARIES} ${Boost_LIBRARIES})
  add_definitions(-DWITH_BBPSDK)
endif()

configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nsol/NsolConfig.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/NsolConfig.h"
  )
include_directories("${CMAKE_CURRENT_BINARY_DIR}")


# Installation rules for both MSVC and UNIX
if (MSVC)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/nson.lib DESTINATION lib)
else()
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libnsol.a DESTINATION lib)
endif()

