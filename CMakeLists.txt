# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   NSOL - NeuroScience Ontology Library
#   2014 (c) GMRV / Universidad Rey Juan Carlos
#   gmrv@gmrv.es
#   www.gmrv.es
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
cmake_minimum_required(VERSION 2.8)
project(nsol)

# Disable in source building
if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
  message(FATAL "no in source building allowed.")
endif()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake
  ${CMAKE_SOURCE_DIR}/CMake/common)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
  add_definitions(-DDEBUG)
endif()

include(GitExternal)

# nsol version
set(LAST_RELEASE 0.0.0)
set(VERSION_MAJOR "0")
set(VERSION_MINOR "1")
set(VERSION_PATCH "0")
set(VERSION_ABI 1)

# description
set(NSOL_DESCRIPTION "Nsol - Neuroscience Ontology Library")
set(COMMON_PROJECT_DOMAIN gmrv.es)

# Option to build with shared pointers or raw pointers
option(WITH_SHARED_PTR "WITH_SHARED_PTR" OFF)
option(WITH_BBPSDK "WITH_BBPSDK" ON)

option( NSOL_WITH_LOGGING "NSOL_WITH_LOGGING" ON )
if ( NSOL_WITH_LOGGING )
  add_definitions( -DNSOL_WITH_LOGGING )
endif( )

include(Common)

common_package(Boost COMPONENTS unit_test_framework)
common_package(vmmlib REQUIRED)
list(APPEND NSOL_DEPENDENT_LIBRARIES vmmlib)

if (WITH_BBPSDK)
  common_package(BBPSDK)
  if( BBPSDK_FOUND )
    list(APPEND NSOL_DEPENDENT_LIBRARIES BBPSDK)
  endif( )
endif()
common_package(Qt5Core)
common_package(fires)
common_package_post()

if(FIRES_FOUND)
  list(APPEND NSOL_DEPENDENT_LIBRARIES fires)
endif()

if(QT5CORE_FOUND)
  list(APPEND NSOL_DEPENDENT_LIBRARIES Qt5Core)
endif()

# library subdirectory
add_subdirectory(nsol)

# tests subdirectory
add_subdirectory(tests)

# examples subdirectory
add_subdirectory(examples)

# examples subdirectory
add_subdirectory(testData)

include(CPackConfig)
include(DoxygenRule)
