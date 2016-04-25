configure_file(${PROJECT_SOURCE_DIR}/testData/ExampleNeuron.swc
  ${CMAKE_CURRENT_BINARY_DIR}/ExampleNeuron.swc)

configure_file(${PROJECT_SOURCE_DIR}/testData/mini.swc
  ${CMAKE_CURRENT_BINARY_DIR}/mini.swc)


if (${Boost_FOUND})
  set(TEST_LIBRARIES
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    nsol
    ${Qt5Core_LIBRARIES}
    )
  include(CommonCTest)
endif()
