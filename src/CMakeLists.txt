cmake_minimum_required (VERSION 2.6)


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
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
if(NOT MACHINE_CONFIG)
#    set(CMAKE_CXX_FLAGS_RELEASE "-Wall -DNDEBUG -O3  -std=c++11 -stdlib=libc++  " CACHE STRING "Compiler flags for Release compiles.")
#    set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -O0 -m64   -std=c++11 -stdlib=libc++  " CACHE STRING "Compiler flags for Debug compiles.")
    set(CMAKE_CXX_FLAGS_RELEASE "-Wall -DNDEBUG -O3  " CACHE STRING "Compiler flags for Release compiles.")
    set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -O0 -m64  " CACHE STRING "Compiler flags for Debug compiles.")
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

option (COREBLURON_TESTS "Build the COREBLURONE regression tests" OFF)
set(SIMD_TECH sse2 CACHE STRING "SIMD technology: sse2,avx,qpx")
option (COREBLURON_FMA "support FMA, very experiemental the parser is not still ready, it can not compile" OFF)
option (COREBLURON_MATH "support lmass lmass_simd from IBM" OFF)
add_definitions(-m${SIMD_TECH} "-D__COREBLURON_SIMD_VALUE__=${SIMD_TECH}")

########################################################################
#
# Find SIMD
#
########################################################################

if(COREBLURON_FMA)
   add_definitions(-mfma) 
endif(COREBLURON_FMA)


########################################################################
#
# math library 
#
########################################################################
if(COREBLURON_MATH)
find_library(MASS_LIBRARY
             NAMES mass
             PATHS /opt/ibmcmp/xlmass/bg/7.3/bglib64/)

find_library(SIMD_MASS_LIBRARY
             NAMES mass_simd
             PATHS /opt/ibmcmp/xlmass/bg/7.3/bglib64/)
endif(COREBLURON_MATH)

########################################################################
#
# Find dependencies
#
########################################################################

#this depends of the associated module
set(Boost_NO_SYSTEM_PATHS TRUE)
set(BOOST_DIR $ENV{BOOST_DIR} CACHE PATH "Path to the Boost installation (or to the Boost source)")
set(BOOST_ROOT ${BOOST_DIR})
#find_package (Boost COMPONENTS unit_test_framework system chrono)
find_package (Boost COMPONENTS unit_test_framework)
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

