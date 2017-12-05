# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   NSOL - NeuroScience Objects Library
#   2014-2017 (c) GMRV / URJC
#   gmrv@gmrv.es
#   www.gmrv.es
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(nsol VERSION 0.3.0 )
set(nsol_VERSION_ABI 3)

# Disable in source building
if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
  message(FATAL "no in source building allowed.")
endif()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake
  ${CMAKE_SOURCE_DIR}/CMake/common)

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/CMake/common/Common.cmake)
  message(FATAL_ERROR "CMake/common missing, run: git submodule update --init")
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
  add_definitions(-DDEBUG)
endif()

include(GitExternal)

# description
set(NSOL_DESCRIPTION "Nsol - Neuroscience Objects Library")
set(COMMON_PROJECT_DOMAIN gmrv.es)

option( NSOL_WITH_EXAMPLES "NSOL_WITH_EXAMPLES" ON )
option( NSOL_WITH_TESTS "NSOL_WITH_TESTS" ON )

# Option to build with shared pointers or raw pointers
# TODO option(NSOL_WITH_SHARED_PTR "WITH_SHARED_PTR" OFF)

option( NSOL_WITH_LOGGING "NSOL_WITH_LOGGING" ON )
if ( NSOL_WITH_LOGGING )
  add_definitions( -DNSOL_WITH_LOGGING )
endif( )

option( NSOL_OPTIONALS_AS_REQUIRED
  "Force optional dependencies as required" OFF )

if ( NSOL_OPTIONALS_AS_REQUIRED )
  set( NSOL_OPTS_FIND_ARGS "REQUIRED" )
else()
  set( NSOL_OPTS_FIND_ARGS "" )
endif()


include(Common)

common_find_package(Boost COMPONENTS unit_test_framework)
common_find_package(Eigen3 SYSTEM REQUIRED)
common_find_package(Qt5Core)
common_find_package(HDF5 COMPONENTS C CXX)
common_find_package(FiReS ${NSOL_OPTS_FIND_ARGS})
common_find_package(Brion ${NSOL_OPTS_FIND_ARGS})

list(APPEND NSOL_DEPENDENT_LIBRARIES Eigen3)

if(HDF5_FOUND)
  list(APPEND NSOL_PUBLIC_INCLUDE_DIRECTORIES ${HDF5_INCLUDE_DIRS})
endif()

if(FIRES_FOUND)
  list(APPEND NSOL_DEPENDENT_LIBRARIES FiReS)
endif()

if(QT5CORE_FOUND)
  list(APPEND NSOL_DEPENDENT_LIBRARIES Qt5Core)
endif()

if( BRION_FOUND )
  list(APPEND NSOL_DEPENDENT_LIBRARIES Brion)
endif( )

common_find_package_post()

add_subdirectory(nsol)
add_subdirectory(tests)
add_subdirectory(examples)
add_subdirectory(testData)

set(DOCS README.md LICENSE.txt)
install( FILES ${DOCS} DESTINATION share/nsol COMPONENT dev)

set(DOXYGEN_MAINPAGE_MD README.md )
set(DOXYGEN_EXTRA_INPUT ${PROJECT_SOURCE_DIR}/README.md)
include(DoxygenRule)

include(CPackConfig)
include(CTest)
