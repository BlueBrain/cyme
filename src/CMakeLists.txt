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
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
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

project (cyme) 
set (CYME_VERSION_MAJOR 0)
set (CYME_VERSION_MINOR 1)
	
########################################################################
#
#
########################################################################

include_directories ("${PROJECT_SOURCE_DIR}/cyme")


########################################################################
#
# Options
#
########################################################################

# Look for modules
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

option (CYME_TESTS "Build the CYMEE regression tests" OFF)
set(SIMD_TECH sse2 CACHE STRING "SIMD technology: sse2, avx, qpx and mic")
option (CYME_FMA "support FMA, very experiemental the parser is not still ready, it can not compile" OFF)
option (CYME_MATH "support lmass lmass_simd from IBM" OFF)
option (CYME_DOCUMENTATION "Use Doxygen to create the HTML/LATEX based API documentation" OFF)
add_definitions(-m${SIMD_TECH} "-D__CYME_SIMD_VALUE__=${SIMD_TECH}")

########################################################################
#
# Find SIMD
#
########################################################################

if(CYME_FMA)
   add_definitions(-mfma -D__FMA__)
endif(CYME_FMA)


########################################################################
#
# math library 
#
########################################################################
if(CYME_MATH)
find_library(MASS_LIBRARY
             NAMES mass
             PATHS /opt/ibmcmp/xlmass/bg/7.3/bglib64/)

find_library(SIMD_MASS_LIBRARY
             NAMES mass_simd
             PATHS /opt/ibmcmp/xlmass/bg/7.3/bglib64/)
endif(CYME_MATH)

########################################################################
#
# Find dependencies
#
########################################################################

#this depends of the associated module
set(Boost_NO_SYSTEM_PATHS TRUE)
set(BOOST_DIR $ENV{BOOST_DIR} CACHE PATH "Path to the Boost installation (or to the Boost source)")
set(BOOST_ROOT ${BOOST_DIR})
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
#find_package (Boost COMPONENTS unit_test_framework system chrono)
find_package (Boost 1.54 COMPONENTS unit_test_framework)
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

if(CYME_TESTS)
    include(CTest)
    enable_testing()
    set(BUILDNAME "${PROJECT_VERSION}" CACHE STRING "Name of build on the dashboard")
      mark_as_advanced(BUILDNAME)
    add_subdirectory (regression)
endif(CYME_TESTS)

########################################################################
#
# Documentation
#
########################################################################

if(CYME_DOCUMENTATION)
  FIND_PACKAGE(Doxygen)
  if (NOT DOXYGEN_FOUND)
    message(FATAL_ERROR 
      "Doxygen is needed to build the documentation. Please install it correctly")
  endif()
  #-- Configure the Template Doxyfile for our specific project
  configure_file(Doxyfile.in 
                 ${PROJECT_BINARY_DIR}/Doxyfile  @ONLY IMMEDIATE)
  #-- Add a custom target to run Doxygen when ever the project is built
  add_custom_target (doc   
                     COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
                     SOURCES ${PROJECT_BINARY_DIR}/Doxyfile)
  # IF you want the documentation to be generated EVERY time you build the project
  # then add the 'ALL' keyword after "doc" from the above command.
endif()




