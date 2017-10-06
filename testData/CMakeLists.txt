set(NSOL_TESTDATA_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(NSOL_BINARY_BIN_DIR ${CMAKE_CURRENT_BINARY_DIR})

configure_file(
  scene.xml.in
  ${NSOL_BINARY_BIN_DIR}/scene.xml
  @ONLY )

configure_file(
  oneColumnScene.xml.in
  ${NSOL_BINARY_BIN_DIR}/oneColumnScene.xml
  @ONLY )
