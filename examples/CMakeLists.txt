

#include_directories(${CMAKE_BINARY_DIR})


add_executable(SwcReader SwcReader.cpp)
target_link_libraries(SwcReader ${NSOL_LIBRARIES})


if (BBPSDK_FOUND)

  add_executable(BBPSDKLoader BBPSDKLoader.cpp)
  target_link_libraries(BBPSDKLoader ${NSOL_LIBRARIES})
#    ${BBPSDK_LIBRARIES} ${Boost_LIBRARIES})
#  add_definitions(-DWITH_BBPSDK)

endif()

add_executable(example1 example1.cpp)
target_link_libraries(example1 ${NSOL_LIBRARIES})

add_executable(example2 example2.cpp)
target_link_libraries(example2 ${NSOL_LIBRARIES})


