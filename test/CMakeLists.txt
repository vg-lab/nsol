

add_executable(test1 test1.cpp)

add_executable(testSwcReader testSwcReader.cpp)


set(BBPSDK_DIR "${BBPSDK_INSTALL_DIR}/share/BBPSDK/CMake")
set(Lunchbox_DIR "${BBPSDK_INSTALL_DIR}/share/Lunchbox/CMake")
set(Brion_DIR "${BBPSDK_INSTALL_DIR}/share/Brion/CMake")

FIND_PACKAGE(BBPSDK)


if (BBPSDK_FOUND)
  message(STATUS "BBPSDK found")
  find_package(Boost 1.45.0 COMPONENTS system REQUIRED)
  INCLUDE_DIRECTORIES(${BBPSDK_INCLUDE_DIRS})
  add_executable(testBBPSDKLoader testBBPSDKLoader.cpp)
  TARGET_LINK_LIBRARIES(testBBPSDKLoader ${BBPSDK_LIBRARIES} ${Boost_LIBRARIES})

endif()

enable_testing()

#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIR})

find_package (Threads)


add_executable(runTests runTests.cpp )
target_link_libraries(runTests gtest ${CMAKE_THREAD_LIBS_INIT})