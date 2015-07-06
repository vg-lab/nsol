

configure_file(${PROJECT_SOURCE_DIR}/testData/ExampleNeuron.swc
  ${CMAKE_CURRENT_BINARY_DIR}/ExampleNeuron.swc)


if (${Boost_FOUND})
  set(TEST_LIBRARIES ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} nsol)
  include(CommonCTest)
endif()
