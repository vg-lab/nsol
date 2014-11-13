
if (${Boost_FOUND})
  set(TEST_LIBRARIES ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} nsol)
  include(CommonCTest)
endif()

