#include_directories(${CMAKE_BINARY_DIR})


# add_executable(SwcReader SwcReader.cpp)
# target_link_libraries(SwcReader ${NSOL_LINK_LIBRARIES} nsol)


if (BBPSDK_FOUND)

  # add_executable(BBPSDKLoader BBPSDKLoader.cpp)
  # target_link_libraries(BBPSDKLoader ${NSOL_LINK_LIBRARIES} nsol)
#    ${BBPSDK_LIBRARIES} ${Boost_LIBRARIES})
#  add_definitions(-DWITH_BBPSDK)

endif()

# add_executable(example1 example1.cpp)
# target_link_libraries(example1 ${NSOL_LINK_LIBRARIES} nsol)

# add_executable(example2 example2.cpp)
# target_link_libraries(example2 ${NSOL_LINK_LIBRARIES} nsol)

add_executable(stats stats.cpp)
target_link_libraries(stats ${NSOL_LINK_LIBRARIES} nsol)
