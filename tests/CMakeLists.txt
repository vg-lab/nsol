if(NSOL_WITH_TESTS)

  # Configure the test data header
  configure_file(
    ${CMAKE_CURRENT_LIST_DIR}/testData.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/testData.h
  )

  # Function to add a test
  function(add_project_test NAME SOURCE)
    add_executable(${NAME} ${SOURCE})
    target_include_directories(${NAME}
      PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
    )
    target_link_libraries(${NAME} PRIVATE
      ${PROJECT_NAME}
      Boost::unit_test_framework
    )
    add_test(NAME ${NAME} COMMAND ${NAME})

    # Create all tests target
    if(NOT TARGET ${PROJECT_NAME}_all_tests)
      add_custom_target(${PROJECT_NAME}_all_tests)
    endif()

    # Add test to global tests target
    add_dependencies(${PROJECT_NAME}_all_tests ${NAME})
  endfunction()

  # Add tests
  add_project_test(nsolTestCached Cached.cpp)
  add_project_test(nsolTestCachedNeuronMorphologySection CachedNeuronMorphologySection.cpp)
  add_project_test(nsolTestCircuit Circuit.cpp)
  add_project_test(nsolTestColumn Column.cpp)
  add_project_test(nsolTestDendrite Dendrite.cpp)
  add_project_test(nsolTestLog Log.cpp)
  add_project_test(nsolTestMiniColumn MiniColumn.cpp)
  add_project_test(nsolTestMorphologySynapse MorphologySynapse.cpp)
  add_project_test(nsolTestNeurite Neurite.cpp)
  add_project_test(nsolTestNeuron Neuron.cpp)
  add_project_test(nsolTestNeuronMorphology NeuronMorphology.cpp)
  add_project_test(nsolTestNeuronMorphologySection NeuronMorphologySection.cpp)
  add_project_test(nsolTestNode Node.cpp)
  add_project_test(nsolTestNodeCache NodeCache.cpp)
  add_project_test(nsolTestObject Object.cpp)
  add_project_test(nsolTestObjectWithProperties ObjectWithProperties.cpp)
  add_project_test(nsolTestReaders Readers.cpp)
  add_project_test(nsolTestScene Scene.cpp)
  add_project_test(nsolTestSection Section.cpp)
  add_project_test(nsolTestSimplifier Simplifier.cpp)
  add_project_test(nsolTestSoma Soma.cpp)
  add_project_test(nsolTestSwcWriter SwcWriter.cpp)
  add_project_test(nsolTestSynapse Synapse.cpp)  

endif()