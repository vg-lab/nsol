

#add_executable(test1 test1.cpp)
#add_executable(testSwcReader testSwcReader.cpp)


set(BBPSDK_DIR "${BBPSDK_INSTALL_DIR}/share/BBPSDK/CMake")
set(Lunchbox_DIR "${BBPSDK_INSTALL_DIR}/share/Lunchbox/CMake")
set(Brion_DIR "${BBPSDK_INSTALL_DIR}/share/Brion/CMake")

FIND_PACKAGE(BBPSDK)

include_directories(${CMAKE_BINARY_DIR})

if (BBPSDK_FOUND)
  message(STATUS "BBPSDK found")
  find_package(Boost 1.45.0 COMPONENTS system REQUIRED)
  include_directories(${BBPSDK_INCLUDE_DIRS} )
  add_executable(testBBPSDKLoader testBBPSDKLoader.cpp)
  target_link_libraries(testBBPSDKLoader nsol ${BBPSDK_LIBRARIES} ${Boost_LIBRARIES})
  add_definitions(-DWITH_BBPSDK)
endif()

enable_testing()

#find_package(gtest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIR})


find_library(GTEST_LIBRARY_DIR 
 NAMES libgtest.a
 PATHS 
 /opt/local/lib
 /usr/local/lib
 /usr/lib
)

#message(${GTEST_LIBRARY_DIR})
if (GTEST_LIBRARY_DIR)

  find_package (Threads)
  add_executable(runTests runTests.cpp )
  target_link_libraries(runTests gtest ${CMAKE_THREAD_LIBS_INIT})

endif()
