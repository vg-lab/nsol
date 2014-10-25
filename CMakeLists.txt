# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   NSOL - NeuroScience Ontology Library
#   2014 (c) GMRV / Universidad Rey Juan Carlos
#   gmrv@gmrv.es
#   www.gmrv.es
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
project(nsol)
cmake_minimum_required(VERSION 2.8)

# Add CMake dir to the module path
list(APPEND CMAKE_MODULE_PATH 
  ${CMAKE_CURRENT_SOURCE_DIR}/CMake)

# Option to build with shared pointers or raw pointers
option(WITH_SHARED_PTR "WITH_SHARED_PTR" OFF)
if (WITH_SHARED_PTR)
  set(NSOL_WITH_SHARED_PTR 1)
else()
  set(NSOL_WITH_SHARED_PTR 0)
endif()


# Standard configs like version, debug as default
include(StandardConfig)

# Custom flags for Release and Debug
if (MSVC)
	set(CMAKE_CXX_FLAGS 
		"${CMAKE_CXX_FLAGS} -W4")
else()
	set(CMAKE_CXX_FLAGS 
		"${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wno-unknown-pragmas")
endif()
set(CMAKE_CXX_FLAGS_DEBUG 
  "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

# Find package vmmlib which is required
find_package(vmmlib REQUIRED)
include_directories(${VMMLIB_INCLUDE_DIRS})

# Find package BBPSDK which is optional
find_package(BBPSDK)
if (BBPSDK_FOUND)
  find_package(Boost 1.45.0 COMPONENTS system REQUIRED)
  include_directories(${BBPSDK_INCLUDE_DIRS})
  add_definitions(-DWITH_BBPSDK)
endif()


# Build library
add_library (${PROJECT_NAME} SHARED
${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/Axon.cpp
${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/Column.cpp
${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/Dendrite.cpp
${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/MiniColumn.cpp
${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/Neurite.cpp
${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/Neuron.cpp
${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/NeuronMorphology.cpp
${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/Node.cpp
${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/Section.cpp
${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/Segment.cpp
${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/Soma.cpp
)
set_target_properties(${CMAKE_PROJECT_NAME}
  PROPERTIES VERSION ${${CMAKE_PROJECT_NAME}_VERSION} SOVERSION ${${CMAKE_PROJECT_NAME}_VERSION}
)

include (GenerateExportHeader)
GENERATE_EXPORT_HEADER( nsol
    BASE_NAME nsol
             EXPORT_MACRO_NAME NSOL_API
             EXPORT_FILE_NAME nsol/api.h
             STATIC_DEFINE nsol_BUILT_AS_STATIC
)

# Set libraries for target
if (BBPSDK_FOUND)
  target_link_libraries(${PROJECT_NAME} ${BBPSDK_LIBRARIES} ${Boost_LIBRARIES})
endif()


# Install rules
# Find files to install 
file(GLOB DEPLOY_FILES_AND_DIRS 
"${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/*"
"${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/Reader*"
"${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/Writer/*"
"${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/Container/*"
)
include(InstallLibrary)

# Doxygen documentation generation
include(Doxygen)

# Test subdirectory 
add_subdirectory(test)

# Export library
include(ExportLibrary)





