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

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake
  ${CMAKE_SOURCE_DIR}/CMake/common)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

include(GitExternal)
GIT_EXTERNAL(CMake/common https://github.com/Eyescale/CMake master)


set(LAST_RELEASE 0.0.0)
set(VERSION_MAJOR "0")
set(VERSION_MINOR "1")
set(VERSION_PATCH "0")
set(VERSION_ABI 1)

set(NSOL_DESCRIPTION "Nsol - Neuroscience Ontology Library")
set(COMMON_PROJECT_DOMAIN gmrv.es)

# Option to build with shared pointers or raw pointers
option(WITH_SHARED_PTR "WITH_SHARED_PTR" OFF)

include(Common)
include(FindPackages) 

add_subdirectory(nsol)
add_subdirectory(test)
add_subdirectory(examples)

include(CPackConfig)
include(DoxygenRule)





