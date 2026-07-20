set(NSOL_TESTDATA_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(NSOL_BINARY_BIN_DIR ${CMAKE_CURRENT_BINARY_DIR})

configure_file(
  scene.xml.in
  ${NSOL_BINARY_BIN_DIR}/scene.xml
  @ONLY
)

configure_file(
  oneColumnScene.xml.in
  ${NSOL_BINARY_BIN_DIR}/oneColumnScene.xml
  @ONLY
)

# Define installation directory variables
include(GNUInstallDirs)

# Install example data
install(DIRECTORY
  ${PROJECT_SOURCE_DIR}/testData
  ${CMAKE_CURRENT_BINARY_DIR}/testData
  DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME_LOWER}
  FILES_MATCHING
    PATTERN "*.asc"  PATTERN "*.swc" PATTERN "*.xml"
)