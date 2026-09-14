cmake_minimum_required(VERSION 3.25)

project(nsol
  VERSION 0.4.1
  LANGUAGES CXX
  DESCRIPTION "NeuroScience Objects Library"
)
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)
string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)

# Prevent in-source builds
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "In-source builds are not allowed. Please create a separate build directory.")
endif()

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

# Include custom modules
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Options
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
option(BUILD_DOCS "Build documentation" ON)
option(NSOL_WITH_EXAMPLES "Build examples" ON)
option(NSOL_WITH_TESTS "Build tests" ON)
option(NSOL_OPTIONALS_AS_REQUIRED "Force optional dependencies as required" OFF)

option(NSOL_WITH_LOGGING "Enable logging" ON)
option(NSOL_USE_SHARED_PTR "" OFF)
option(NSOL_USE_BRION "" ON)
option(NSOL_USE_FIRES "" ON)

# Dependencies
find_package(Boost CONFIG REQUIRED COMPONENTS unit_test_framework)
find_package(Eigen3 REQUIRED NO_MODULE)
# find_package(Qt5 COMPONENTS Core)
# find_package(HDF5 COMPONENTS C CXX)
# find_package(OpenMP)

# Optional dependencies
set(NSOL_OPTS_FIND_ARGS "")
if(NSOL_OPTIONALS_AS_REQUIRED)
  set(NSOL_OPTS_FIND_ARGS REQUIRED)
endif()

find_package(Qt5 ${NSOL_OPTS_FIND_ARGS} COMPONENTS Core)
find_package(HDF5 ${NSOL_OPTS_FIND_ARGS} COMPONENTS C CXX)
find_package(OpenMP ${NSOL_OPTS_FIND_ARGS})
# find_package(FiReS ${NSOL_OPTS_FIND_ARGS} QUIET)
# find_package(Brion ${NSOL_OPTS_FIND_ARGS} QUIET)

if(NSOL_USE_BRION)
  include(FetchContent)
  FetchContent_Declare(
      Brion
      GIT_REPOSITORY https://github.com/vg-lab/Brion.git
      GIT_SHALLOW ON
      FIND_PACKAGE_ARGS
  )
  FetchContent_MakeAvailable(Brion)
endif()

if(NSOL_USE_FIRES)
  FetchContent_Declare(
      FiReS
      GIT_REPOSITORY https://github.com/vg-lab/FiReS.git
      GIT_SHALLOW ON
      FIND_PACKAGE_ARGS
  )
  FetchContent_MakeAvailable(FiReS)
endif()

# Definitions
option(NSOL_USE_HDF5 "" ${HDF5_FOUND})
option(NSOL_USE_QT5CORE "" ${Qt5Core_FOUND})
option(NSOL_USE_OPENMP "" ${OpenMP_FOUND})
# option(NSOL_USE_BRION "" ${Brion_FOUND})
# option(NSOL_USE_FIRES "" ${FiReS_FOUND})

# Add subdirectories
add_subdirectory(${PROJECT_NAME_LOWER})

add_subdirectory(testData)

# Don't build tests when others include the library
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND NSOL_WITH_TESTS)
  include(CTest)
  add_subdirectory(tests)
endif()

# Don't build examples when others include the library
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND NSOL_WITH_EXAMPLES)
  add_subdirectory(examples)
endif()

# Define installation directory variables
include(GNUInstallDirs)

# Create an export
install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME_LOWER}
  FILE_SET public_headers DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILE_SET public_headers_generated DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install the project targets file
install(EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME_LOWER}-targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME_LOWER}
)

# Include the CMake module that provides helpers for creating package config files
include(CMakePackageConfigHelpers)

# Generate the project-specific cmake config file
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/project-config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME_LOWER}-config.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME_LOWER}
)

# Generate the project-specific cmake config version file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME_LOWER}-config-version.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

# Install the cmake config files
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME_LOWER}-config.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME_LOWER}-config-version.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME_LOWER}
)

# Install repo data
install(FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/README.md"
  "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt"
  DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME_LOWER}
)

# Allow the configured project-config.cmake in the build directory to be used by
# other projects, without needing it to be installed
export(EXPORT ${PROJECT_NAME}Targets
  NAMESPACE ${PROJECT_NAME}::
  FILE ${PROJECT_NAME_LOWER}-targets.cmake
)

# Generate documentation
find_package(Doxygen)
if(DOXYGEN_FOUND AND BUILD_DOCS)
  set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/docs_doxygen)
  set(DOXYFILE_IN ${PROJECT_SOURCE_DIR}/cmake/Doxyfile.in)
  set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

  configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

  doxygen_add_docs(
    ${PROJECT_NAME}_doxygen
    CONFIG_FILE ${DOXYFILE_OUT}
  )

  install(DIRECTORY
    ${DOXYGEN_OUTPUT_DIR}/html
    DESTINATION ${CMAKE_INSTALL_DOCDIR}
    COMPONENT ${PROJECT_NAME}_documentation
    OPTIONAL
  )
endif()

# Packaging
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE.txt")
set(CPACK_RESOURCE_FILE_README "${PROJECT_SOURCE_DIR}/README.md")
set(CPACK_SOURCE_GENERATOR "TGZ")
include(CPack)
