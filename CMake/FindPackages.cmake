# generated by Buildyard, do not edit.

include(System)
list(APPEND FIND_PACKAGES_DEFINES ${SYSTEM})
find_package(PkgConfig)

# Find package vmmlib which is required
find_package(vmmlib REQUIRED)
include_directories(${VMMLIB_INCLUDE_DIRS})
if(VMMLIB_FOUND)
  set(vmmlib_name LIBVMMLIB)
  set(vmmlib_FOUND TRUE)
elseif(vmmlib_FOUND)
  set(vmmlib_name libzmq)
  set(vmmlib_FOUND TRUE)
endif()
if(vmmlib_name)
  list(APPEND FIND_PACKAGES_DEFINES NSOL_WITH_VMMLIB)
  set(FIND_PACKAGES_FOUND "${FIND_PACKAGES_FOUND} vmmlib")
#  link_directories(${${vmmlib_name}_LIBRARY_DIRS})
  if(NOT "${${libvmmlib_name}_INCLUDE_DIRS}" MATCHES "-NOTFOUND")
    include_directories(${${libvmmlib_name}_INCLUDE_DIRS})
  endif()
endif()

# Find package BBPSDK which is optional
if(WITH_BBPSDK)

  find_package(BBPSDK)

  if(BBPSDK_FOUND)
    set(bbpsdk_name LIBBBPSDK)
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
      include_directories(${${libbbpsdk_name}_INCLUDE_DIRS})
    endif()
    
    #  list(APPEND NSOL_LIBRARIES ${BBPSDK_LIBRARIES})
  endif()
endif()

# if (BBPSDK_FOUND)
#   include_directories(${BBPSDK_INCLUDE_DIRS})
#   add_definitions(-DWITH_BBPSDK)
# endif()


# Option of shared pointers
if (WITH_SHARED_PTR)
#  set(WITH_SHARED_PTR 1)
  list(APPEND FIND_PACKAGES_DEFINES NSOL_WITH_SHARED_PTR) 
endif()


#set(NSOL_DEPENDS vmmlib;bbpsdk)

# Write defines.h and options.cmake
if(NOT PROJECT_INCLUDE_NAME)
  message(WARNING "PROJECT_INCLUDE_NAME not set, old or missing Common.cmake?")
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
  message(WARNING "CMAKE_MODULE_INSTALL_PATH not set, old or missing Common.cmake?")
endif()
file(APPEND ${DEFINES_FILE_IN}
  "\n#endif\n")

include(UpdateFile)
configure_file(${DEFINES_FILE_IN} ${DEFINES_FILE} COPYONLY)

if(FIND_PACKAGES_FOUND)
  if(MSVC)
    message(STATUS "Configured ${PROJECT_NAME} with ${FIND_PACKAGES_FOUND}")
  else()
    message(STATUS "Configured ${PROJECT_NAME} with ${CMAKE_BUILD_TYPE}${FIND_PACKAGES_FOUND}")
  endif()
endif()

# set(NSOL_DEPENDENT_LIBRARIES "${NSOL_DEPENDENT_LIBRARIES}" PARENT_SCOPE)
