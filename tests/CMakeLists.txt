if ( NSOL_WITH_TESTS )
  configure_file(${PROJECT_SOURCE_DIR}/testData/ExampleNeuron.swc
    ${CMAKE_CURRENT_BINARY_DIR}/ExampleNeuron.swc)

  configure_file(${PROJECT_SOURCE_DIR}/testData/mini.swc
    ${CMAKE_CURRENT_BINARY_DIR}/mini.swc)

  configure_file(${PROJECT_SOURCE_DIR}/tests/testData.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/testData.h)

  include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

  if (${Boost_FOUND})
    set(TEST_LIBRARIES
      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
      nsol
      ${Qt5Core_LIBRARIES}
      )
    include(CommonCTest)
  endif()
endif()
