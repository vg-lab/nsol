
include(System)
list(APPEND FIND_PACKAGES_DEFINES ${SYSTEM})
find_package(PkgConfig)

# Find boost unit_test_framework for tests
if(PKG_CONFIG_EXECUTABLE)
  find_package(Boost COMPONENTS unit_test_framework)
  if((NOT Boost_FOUND) AND (NOT BOOST_FOUND))
    pkg_check_modules(Boost Boost>=1.41.0)
  endif()
  if((NOT Boost_FOUND) AND (NOT BOOST_FOUND))
    message(FATAL_ERROR 
      "Could not find Boost COMPONENTS unit_test_framework")
  endif()
else()
  find_package(Boost COMPONENTS unit_test_framework)
endif()


if(BOOST_FOUND)
  set(Boost_name BOOST)
  set(Boost_FOUND TRUE)
elseif(Boost_FOUND)
  set(Boost_name Boost)
  set(BOOST_FOUND TRUE)
endif()
if(Boost_name)
  list(APPEND FIND_PACKAGES_DEFINES NSOL_USE_BOOST)
  if(NOT COMMON_LIBRARY_TYPE MATCHES "SHARED")
    list(APPEND NSOL_DEPENDENT_LIBRARIES Boost)
  endif()
  set(FIND_PACKAGES_FOUND "${FIND_PACKAGES_FOUND} Boost")
  link_directories(${${Boost_name}_LIBRARY_DIRS})
  if(NOT "${${Boost_name}_INCLUDE_DIRS}" MATCHES "-NOTFOUND")
    include_directories(SYSTEM ${${Boost_name}_INCLUDE_DIRS})
  endif()
endif()

# Find package vmmlib which is required
find_package(vmmlib REQUIRED)
include_directories(${VMMLIB_INCLUDE_DIRS})
if(VMMLIB_FOUND)
  set(vmmlib_name LIBVMMLIB)
  set(vmmlib_FOUND TRUE)
elseif(vmmlib_FOUND)
  set(vmmlib_name LIBVMMLIB)
  set(vmmlib_FOUND TRUE)
endif()
if(vmmlib_name)
  list(APPEND FIND_PACKAGES_DEFINES NSOL_WITH_VMMLIB)
  set(FIND_PACKAGES_FOUND "${FIND_PACKAGES_FOUND} vmmlib")
  if(NOT "${${libvmmlib_name}_INCLUDE_DIRS}" MATCHES "-NOTFOUND")
    include_directories(${${libvmmlib_name}_INCLUDE_DIRS})
  endif()
endif()

# Find package BBPSDK which is optional
if(WITH_BBPSDK)
  find_package(BBPSDK)
  if(BBPSDK_FOUND)
    set(bbpsdk_name BBPSDK)
    set(bbpsdk_FOUND TRUE)
  elseif(bbpsdk_FOUND)
    set(bbpsdk_name libzmq)
    set(bbpsdk_FOUND TRUE)
  endif()
  if(bbpsdk_name)

    list(APPEND NSOL_DEPENDENT_LIBRARIES BBPSDK)

    find_package(Boost 1.45.0 COMPONENTS system REQUIRED)
    list(APPEND FIND_PACKAGES_DEFINES NSOL_WITH_BBPSDK)
    set(FIND_PACKAGES_FOUND "${FIND_PACKAGES_FOUND} bbpsdk")
    link_directories(${${bbpsdk_name}_LIBRARY_DIRS})
    if(NOT "${${libbbpsdk_name}_INCLUDE_DIRS}" MATCHES "-NOTFOUND")
      include_directories(${${bbpsdk_name}_INCLUDE_DIRS})
    endif()   
    #  list(APPEND NSOL_LIBRARIES ${BBPSDK_LIBRARIES})
  endif()
endif()

find_package(Qt5Core)
if(QT5CORE_FOUND)
  set(Qt5Core_name QT5CORE)
  set(Qt5Core_FOUND TRUE)
elseif(Qt5Core_FOUND)
  set(Qt5Core_name Qt5Core)
  set(QT5CORE_FOUND TRUE)
endif()
if(Qt5Core_name)
  list(APPEND FIND_PACKAGES_DEFINES NSOL_WITH_QT5CORE)
  list(APPEND NSOL_DEPENDENT_LIBRARIES Qt5Core)
  set(FIND_PACKAGES_FOUND "${FIND_PACKAGES_FOUND} Qt5Core")
  link_directories(${${Qt5Core_name}_LIBRARY_DIRS})
  if(NOT "${${Qt5Core_name}_INCLUDE_DIRS}" MATCHES "-NOTFOUND")
    include_directories(${${Qt5Core_name}_INCLUDE_DIRS})
  endif()
  if(NOT "${${Qt5Core_name}_INCLUDE_DIR}" MATCHES "-NOTFOUND")
    include_directories(${${Qt5Core_name}_INCLUDE_DIR})
  endif()
endif()


# Option of shared pointers
if (WITH_SHARED_PTR)
#  set(WITH_SHARED_PTR 1)
  list(APPEND FIND_PACKAGES_DEFINES NSOL_WITH_SHARED_PTR) 
endif()

# Write defines.h and options.cmake
if(NOT PROJECT_INCLUDE_NAME)
  message(WARNING 
    "PROJECT_INCLUDE_NAME not set, old or missing Common.cmake?")
  set(PROJECT_INCLUDE_NAME ${PROJECT_NAME})
endif()
if(NOT OPTIONS_CMAKE)
  set(OPTIONS_CMAKE ${CMAKE_CURRENT_BINARY_DIR}/options.cmake)
endif()
set(DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_INCLUDE_NAME}/defines${SYSTEM}.h")
list(APPEND COMMON_INCLUDES ${DEFINES_FILE})
set(DEFINES_FILE_IN ${DEFINES_FILE}.in)
file(WRITE ${DEFINES_FILE_IN}
  "// generated by CMake/FindPackages.cmake, do not edit.\n\n"
  "#ifndef ${PROJECT_NAME}_DEFINES_${SYSTEM}_H\n"
  "#define ${PROJECT_NAME}_DEFINES_${SYSTEM}_H\n\n")
file(WRITE ${OPTIONS_CMAKE} "# Optional modules enabled during build\n")
foreach(DEF ${FIND_PACKAGES_DEFINES})
  add_definitions(-D${DEF}=1)
  file(APPEND ${DEFINES_FILE_IN}
  "#ifndef ${DEF}\n"
  "#  define ${DEF} 1\n"
  "#endif\n")
if(NOT DEF STREQUAL SYSTEM)
  file(APPEND ${OPTIONS_CMAKE} "set(${DEF} ON)\n")
endif()
endforeach()
if(CMAKE_MODULE_INSTALL_PATH)
  install(FILES ${OPTIONS_CMAKE} DESTINATION ${CMAKE_MODULE_INSTALL_PATH}
    COMPONENT dev)
else()
  message(WARNING 
    "CMAKE_MODULE_INSTALL_PATH not set, old or missing Common.cmake?")
endif()
file(APPEND ${DEFINES_FILE_IN}
  "\n#endif\n")

include(UpdateFile)
configure_file(${DEFINES_FILE_IN} ${DEFINES_FILE} COPYONLY)

if(FIND_PACKAGES_FOUND)
  if(MSVC)
    message(STATUS 
      "Configured ${PROJECT_NAME} with ${FIND_PACKAGES_FOUND}")
  else()
    message(STATUS 
      "Configured ${PROJECT_NAME} with ${CMAKE_BUILD_TYPE}${FIND_PACKAGES_FOUND}")
  endif()
endif()


