cmake_minimum_required (VERSION 2.8)


######################################################################
# Machine Config
######################################################################

if(MACHINE_CONFIG)
  if(EXISTS ${MACHINE_CONFIG})
    message(STATUS "Loading config in " ${MACHINE_CONFIG})
    include(${MACHINE_CONFIG})
  else(EXISTS ${MACHINE_CONFIG})
    message(ERROR " Machine config not found!")
  endif(EXISTS ${MACHINE_CONFIG})
endif(MACHINE_CONFIG)
set(CMAKE_INSTALL_PREFIX "/opt/corebluron" CACHE STRING "Install path prefix, prepended onto install directories.")
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
if(NOT MACHINE_CONFIG)
    set(CMAKE_CXX_FLAGS_RELEASE "-Wall -DNDEBUG -O3" CACHE STRING "Compiler flags for Release compiles.")
    set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -O0 -m64" CACHE STRING "Compiler flags for Debug compiles.")
endif(NOT MACHINE_CONFIG)



########################################################################
#
# Project and version information
#
########################################################################

project (corebluron)
set (COREBLURON_VERSION_MAJOR 0)
set (COREBLURON_VERSION_MINOR 1)

########################################################################
#
# Options
#
########################################################################

# Look for modules
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

option (COREBLURON_TESTS "Build the COREBLURONE regression tests" ON)

########################################################################
#
# Find dependencies
#
########################################################################

#this depends of the associated module
set(BOOST_DIR $ENV{BOOST_DIR} CACHE PATH "Path to the Boost installation (or to the Boost source)")
set(BOOST_ROOT ${BOOST_DIR})
find_package (Boost COMPONENTS unit_test_framework system)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Boost libraries not found. Please specify location using the BOOST_DIR variable")
endif()


########################################################################
#
# Compile and prepare library
#
########################################################################
include_directories ("${PROJECT_BINARY_DIR}")
include_directories ("${PROJECT_SOURCE_DIR}")
add_subdirectory( main/ )
#include_directories ("${PROJECT_SOURCE_DIR}/memory/")

########################################################################
#
# Tests
#
########################################################################

if(COREBLURON_TESTS)
    include(CTest)
    enable_testing()
    set(BUILDNAME "${PROJECT_VERSION}" CACHE STRING "Name of build on the dashboard")
      mark_as_advanced(BUILDNAME)
    add_subdirectory (regression)
endif(COREBLURON_TESTS)

