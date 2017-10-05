set(CPACK_PACKAGE_CONTACT "Pablo Toharia <pablo.toharia@urjc.es>")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_SOURCE_DIR}/README.md")

set(CPACK_DEBIAN_PACKAGE_DEPENDS "libeigen3-dev qtbase5-dev")

include(CommonCPack)
