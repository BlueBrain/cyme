set(CPACK_PACKAGE_CONTACT "Tim Ewart <timothee.ewart@epfl.ch>")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.txt" )
set(CPACK_PACKAGE_LICENSE "Proprietary") # change me
set(CPACK_DEBIAN_PACKAGE_DEPENDS
  "libboost-chrono, libboost-system-dev, libboost-test-dev")

include(CommonCPack)
