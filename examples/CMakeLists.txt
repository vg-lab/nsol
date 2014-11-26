#include_directories(${CMAKE_BINARY_DIR})


add_executable(SwcReader SwcReader.cpp)
target_link_libraries(SwcReader ${NSOL_LINK_LIBRARIES} nsol)


if (BBPSDK_FOUND)

  add_executable(BBPSDKLoader BBPSDKLoader.cpp)
  target_link_libraries(BBPSDKLoader ${NSOL_LINK_LIBRARIES} nsol)
 add_definitions(-DWITH_BBPSDK)

endif()

add_executable(example1 example1.cpp)
target_link_libraries(example1 ${NSOL_LINK_LIBRARIES} nsol)

add_executable(example2 example2.cpp)
target_link_libraries(example2 ${NSOL_LINK_LIBRARIES} nsol)

add_executable(sectionStats sectionStats.cpp)
target_link_libraries(sectionStats ${NSOL_LINK_LIBRARIES} nsol)

add_executable(neuriteStats neuriteStats.cpp)
target_link_libraries(neuriteStats ${NSOL_LINK_LIBRARIES} nsol)

add_executable(neuronStats neuronStats.cpp)
target_link_libraries(neuronStats ${NSOL_LINK_LIBRARIES} nsol)

add_executable(miniColumnStats miniColumnStats.cpp)
target_link_libraries(miniColumnStats ${NSOL_LINK_LIBRARIES} nsol)
