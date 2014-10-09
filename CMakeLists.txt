
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
set(CMAKE_CXX_FLAGS 
  "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wno-unknown-pragmas")
set(CMAKE_CXX_FLAGS_DEBUG 
  "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

# Include directories
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/ 
  ${CMAKE_CURRENT_BINARY_DIR}
) 

# # # # # # # # # # # # # # # # # # # #  # # # # # # # # # # # # # # # # #
# Find files to install 
# # # # # # # # # # # # # # # # # # # # ## # # # # # # # # # # # # # # # # 
file(GLOB DEPLOY_FILES_AND_DIRS 
"${CMAKE_CURRENT_SOURCE_DIR}/nsol/*"
"${CMAKE_CURRENT_SOURCE_DIR}/nsol/Reader*"
"${CMAKE_CURRENT_SOURCE_DIR}/nsol/Writer/*"
"${CMAKE_CURRENT_SOURCE_DIR}/nsol/Container/*"
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
install( FILES ${FILES_TO_DEPLOY} DESTINATION include/nsol )
install( FILES ${CMAKE_CURRENT_BINARY_DIR}/nsol/NsolConfig.h 
  DESTINATION include/nsol )
install( DIRECTORY ${DIRS_TO_DEPLOY} DESTINATION include/nsol )
# # # # # # # # # # # # # # # # # # # # # #  # # # # # # # # # # # # # # #


# Build library
add_library (nsol SHARED
${CMAKE_CURRENT_SOURCE_DIR}/nsol/Axon.cpp
${CMAKE_CURRENT_SOURCE_DIR}/nsol/Column.cpp
${CMAKE_CURRENT_SOURCE_DIR}/nsol/Dendrite.cpp
${CMAKE_CURRENT_SOURCE_DIR}/nsol/MiniColumn.cpp
${CMAKE_CURRENT_SOURCE_DIR}/nsol/Neurite.cpp
${CMAKE_CURRENT_SOURCE_DIR}/nsol/Neuron.cpp
${CMAKE_CURRENT_SOURCE_DIR}/nsol/NeuronMorphology.cpp
${CMAKE_CURRENT_SOURCE_DIR}/nsol/Node.cpp
${CMAKE_CURRENT_SOURCE_DIR}/nsol/Section.cpp
${CMAKE_CURRENT_SOURCE_DIR}/nsol/Segment.cpp
${CMAKE_CURRENT_SOURCE_DIR}/nsol/Soma.cpp
)

option(WITH_SHARED_PTR "WITH_SHARED_PTR" OFF)

if (WITH_SHARED_PTR)
#  add_definitions(-DWITH_SHARED_PTR)
set(NSOL_WITH_SHARED_PTR 1)
else()
set(NSOL_WITH_SHARED_PTR 0)
endif()

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
  target_link_libraries(nsol ${BBPSDK_LIBRARIES} ${Boost_LIBRARIES})
  add_definitions(-DWITH_BBPSDK)
endif()

# Configure file 
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/nsol/NsolConfig.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/nsol/NsolConfig.h"
  )

set_target_properties(nsol
  PROPERTIES VERSION ${nsol_VERSION} SOVERSION ${nsol_VERSION}
)


set(INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include)
set(INSTALL_LIB_DIR ${CMAKE_INSTALL_PREFIX}/lib)
set(INSTALL_CMAKE_DIR ${CMAKE_INSTALL_PREFIX}/share/nsol/CMake)

install(TARGETS nsol
  EXPORT nsolTargets
  DESTINATION ${INSTALL_LIB_DIR}
  COMPONENT dev)


# Installation rules for both MSVC and UNIX
# if (MSVC)
# install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/nsol.lib DESTINATION lib)
# else()
# #  install(TARGETS ${CMAKE_CURRENT_BINARY_DIR}/libnsol.a DESTINATION lib)
#   install(TARGETS nsol DESTINATION lib)
# endif()

# Test subdirectory 
add_subdirectory(test)


# Doxygen documentation generation
find_package(Doxygen)
if(DOXYGEN_FOUND)

  execute_process(
    COMMAND ${CMAKE_COMMAND} -E make_directory "doc"
    RESULT_VARIABLE nok ERROR_VARIABLE error
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
  if(nok)
    message(FATAL_ERROR "Error making building dir in " ${CMAKE_CURRENT_BINARY_DIR}": ${nok}\n")
  endif()

  configure_file(${CMAKE_SOURCE_DIR}/doc/Doxyfile
    ${CMAKE_BINARY_DIR}/doc/Doxyfile @ONLY)


  add_custom_target(doc
    COMMAND ${DOXYGEN_EXECUTABLE} 
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/doc"
    )

endif()




# Add all targets to the build-tree export set
export(TARGETS nsol
  FILE "${PROJECT_BINARY_DIR}/nsolTargets.cmake")
 
# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE nsol)
 
# Create the nsolConfig.cmake and nsolConfigVersion files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
   "${INSTALL_INCLUDE_DIR}")
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(CMake/nsolConfig.cmake.in
  "${PROJECT_BINARY_DIR}/nsolConfig.cmake" @ONLY)
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${FOOBAR_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(CMake/nsolConfig.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/nsolConfig.cmake" @ONLY)
# ... for both
configure_file(CMake/nsolConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/nsolConfigVersion.cmake" @ONLY)
 
# Install the FooBarConfig.cmake and FooBarConfigVersion.cmake
install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/nsolConfig.cmake"
  "${PROJECT_BINARY_DIR}/nsolConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)
 
# Install the export set for use with the install-tree
install(EXPORT nsolTargets DESTINATION
  "${INSTALL_CMAKE_DIR}" COMPONENT dev)
