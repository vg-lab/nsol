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

# Version numbers
set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 1)
set(${PROJECT_NAME}_VERSION_PATCH 0)
set(${PROJECT_NAME}_VERSION
    ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH})

# Default build type is Debug 
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)


# Custom flags for Release and Debug
set(CMAKE_CXX_FLAGS 
  "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wno-unknown-pragmas")
set(CMAKE_CXX_FLAGS_DEBUG 
  "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

# Install dirs
set(INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include)
set(INSTALL_LIB_DIR ${CMAKE_INSTALL_PREFIX}/lib)
set(INSTALL_CMAKE_DIR ${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}/CMake)

# Include directories
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/ 
  ${CMAKE_CURRENT_BINARY_DIR}
) 


option(WITH_SHARED_PTR "WITH_SHARED_PTR" OFF)

if (WITH_SHARED_PTR)
  set(NSOL_WITH_SHARED_PTR 1)
else()
  set(NSOL_WITH_SHARED_PTR 0)
endif()

# # # # # # # # # # # # # # # # # # # #  # # # # # # # # # # # # # # # # #
# Find files to install 
# # # # # # # # # # # # # # # # # # # # ## # # # # # # # # # # # # # # # # 
file(GLOB DEPLOY_FILES_AND_DIRS 
"${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/*"
"${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/Reader*"
"${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/Writer/*"
"${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/Container/*"
)

foreach(ITEM ${DEPLOY_FILES_AND_DIRS})
   if( IS_DIRECTORY "${ITEM}" )
      list( APPEND DIRS_TO_DEPLOY "${ITEM}" )
   else()
     get_filename_component(FILE_EXT "${ITEM}" "EXT")
     if( FILE_EXT STREQUAL ".h" )
       list( APPEND FILES_TO_DEPLOY "${ITEM}" )
     endif()
   endif()
endforeach()
install( FILES ${FILES_TO_DEPLOY} DESTINATION include/${CMAKE_PROJECT_NAME} )
install( FILES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}/config.h 
  DESTINATION include/${CMAKE_PROJECT_NAME} )
install( DIRECTORY ${DIRS_TO_DEPLOY} DESTINATION include/${CMAKE_PROJECT_NAME} )
# # # # # # # # # # # # # # # # # # # # # #  # # # # # # # # # # # # # # #

# Configure file 
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/config.h"
  )


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


# BBPSDK setup
#set(BBPSDK_DIR "${BBPSDK_INSTALL_DIR}/share/BBPSDK/CMake")
#set(Lunchbox_DIR "${BBPSDK_INSTALL_DIR}/share/Lunchbox/CMake")
#set(Brion_DIR "${BBPSDK_INSTALL_DIR}/share/Brion/CMake")


find_package(vmmlib REQUIRED)
include_directories(${VMMLIB_INCLUDE_DIRS})


 
find_package(BBPSDK)
if (BBPSDK_FOUND)
  # message(STATUS "BBPSDK found")
  find_package(Boost 1.45.0 COMPONENTS system REQUIRED)
  include_directories(${BBPSDK_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME} ${BBPSDK_LIBRARIES} ${Boost_LIBRARIES})
  add_definitions(-DWITH_BBPSDK)
endif()

# Install rules
include(InstallLibrary)

# Doxygen documentation generation
include(Doxygen)

# Test subdirectory 
add_subdirectory(test)

# Export library
include(ExportLibrary)





