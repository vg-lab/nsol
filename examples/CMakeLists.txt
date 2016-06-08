add_executable(nsolSwcReader SwcReader.cpp)
target_link_libraries(nsolSwcReader nsol)

add_executable(nsolBrionReaderFile BrionReaderFile.cpp)
target_link_libraries(nsolBrionReaderFile nsol)

if (BBPSDK_FOUND)
  add_executable(nsolBBPSDKLoader BBPSDKLoader.cpp)
  target_link_libraries(nsolBBPSDKLoader nsol)
  add_definitions(-DWITH_BBPSDK)
endif()

add_executable(nsolExtractNeuronStats nsolExtractNeuronStats.cpp)
target_link_libraries(nsolExtractNeuronStats nsol)

add_executable(nsolExample1 example1.cpp)
target_link_libraries(nsolExample1 nsol)

add_executable(nsolExample2 example2.cpp)
target_link_libraries(nsolExample2 nsol)

add_executable(nsolSectionStats sectionStats.cpp)
target_link_libraries(nsolSectionStats nsol)

add_executable(nsolRadiusStat radiusStat.cpp)
target_link_libraries(nsolRadiusStat nsol)

add_executable(nsolNeuriteStats neuriteStats.cpp)
target_link_libraries(nsolNeuriteStats nsol)

add_executable(nsolNeuronStats neuronStats.cpp)
target_link_libraries(nsolNeuronStats nsol)

add_executable(nsolMiniColumnStats miniColumnStats.cpp)
target_link_libraries(nsolMiniColumnStats nsol)

add_executable(nsolFactory factory.cpp)
target_link_libraries(nsolFactory nsol)

add_executable(nsolDataset dataset.cpp)
target_link_libraries(nsolDataset nsol)

add_executable(nsolSimplifier simplifier.cpp)
target_link_libraries(nsolSimplifier nsol)

if (QT5CORE_FOUND)
  add_executable(nsolScene scene.cpp)
  target_link_libraries(nsolScene
    ${NSOL_LINK_LIBRARIES}
    nsol
 )
endif( )
