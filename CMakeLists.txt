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

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake
  ${CMAKE_SOURCE_DIR}/CMake/common)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

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

include(Common)
include(FindPackages) 

# library subdirectory 
add_subdirectory(nsol)

# tests subdirectory 
add_subdirectory(tests)

# examples subdirectory
add_subdirectory(examples)

include(CPackConfig)
include(DoxygenRule)





