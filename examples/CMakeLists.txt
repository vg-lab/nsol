add_executable(SwcReader SwcReader.cpp)
target_link_libraries(SwcReader nsol)

if (BBPSDK_FOUND)
  add_executable(BBPSDKLoader BBPSDKLoader.cpp)
  target_link_libraries(BBPSDKLoader nsol)
  add_definitions(-DWITH_BBPSDK)
endif()

add_executable(example1 example1.cpp)
target_link_libraries(example1 nsol)

add_executable(example2 example2.cpp)
target_link_libraries(example2 nsol)

add_executable(sectionStats sectionStats.cpp)
target_link_libraries(sectionStats nsol)

add_executable(radiusStat radiusStat.cpp)
target_link_libraries(radiusStat nsol)

add_executable(neuriteStats neuriteStats.cpp)
target_link_libraries(neuriteStats nsol)

add_executable(neuronStats neuronStats.cpp)
target_link_libraries(neuronStats nsol)

add_executable(miniColumnStats miniColumnStats.cpp)
target_link_libraries(miniColumnStats nsol)

add_executable(factory factory.cpp)
target_link_libraries(factory nsol)

add_executable(dataset dataset.cpp)
target_link_libraries(dataset nsol)

if (QT5CORE_FOUND)
  add_executable(scene scene.cpp)
  target_link_libraries(scene
    ${NSOL_LINK_LIBRARIES}
    nsol
 )
endif( )
