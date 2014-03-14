set(CPACK_PACKAGE_CONTACT "Tim Ewart <timothee.ewart@epfl.ch>") # change me
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.txt" ) # change me
set(CPACK_PACKAGE_LICENSE "Proprietary") # change me
#set(CPACK_PROJECT_NAME "cyme") # optional; if not set, CMAKE_PROJECT_NAME is used
 
# fill in your required dependencies for debian-based systems
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-chrono, libboost-system-dev, libboost-test-dev")
 
include(CommonCPack)
# use this to enable module creation on known BBP machines
include(GNUModules)
