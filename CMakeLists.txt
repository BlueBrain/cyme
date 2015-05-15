#@author Ewart
#@date 2013-13-03

#@remarks Copyright BBP/EPFL 2005-2014; All rights reserved

cmake_minimum_required (VERSION 2.8)

########################################################################
#
# Project and version information
#
########################################################################

project (cyme)

set(LAST_RELEASE 1.2.0)
set(VERSION_MAJOR "1")
set(VERSION_MINOR "3")
set(VERSION_PATCH "0")
set(VERSION_ABI "1")

######################################################################
#
# CMake Modules Buildyard and description
#
######################################################################
set(CYME_DESCRIPTION "SIMD computation over user cyme container")

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake
  ${PROJECT_SOURCE_DIR}/CMake/common)
include(GitExternal)

# some common set up of two version
if(COMMON_LIBRARY_TYPE MATCHES "STATIC")
  set(Boost_USE_STATIC_LIBS ON) # to avoid conflict with common
endif()
set(BOOST_MIN_VERSION "1.49.0") # old is bad
set(COMMON_PROJECT_DOMAIN ch.epfl.bluebrain)
include(Common)
include(FindPackages)

########################################################################
#
# Options
#
########################################################################

option (CYME_MAIN "Build the main (sandbox)" ON)
option (CYME_LIBRARY "Build a library for serial computation" ON)
option (CYME_TESTS "Build the CYME regression tests" ON)
option (CYME_MATH "support lmass lmass_simd from IBM" OFF)
option (CYME_MIC_HOST "Check if MIC is install" OFF)

########################################################################
#
#  SIMD
#
########################################################################

# for SIMD detection
include(CheckCXXSourceCompiles)
include(CheckCXXCompilerFlag)
include(CheckCXXSourceRuns)

find_package(SIMD)
find_package(FMA)
find_package(SLURM)

if(CYME_MIC_HOST)
   find_package (MIC)
endif(CYME_MIC_HOST)

include(SelectTech)

########################################################################
#
# Find BOOST dependencies
#
########################################################################

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
  set(CYME_TIME "-lrt") #boost test has a dependency with system time
endif()

########################################################################
#
# Machine dependencies
#
# - Apple: x86 only
# - BG/Q: remove dynamic link and c++11
#
########################################################################

if(APPLE)
   list(REMOVE_ITEM CMAKE_OSX_ARCHITECTURES i386) # cyme does not support 32bit
   set(CMAKE_OSX_ARCHITECTURES ${CMAKE_OSX_ARCHITECTURES} CACHE
     STRING "Build architectures for OS X" FORCE)
endif()

set(VAR $ENV{CLUSTER})
if(VAR STREQUAL bgq) #it is dirty ...
  string(REPLACE "-std=c++11" " " CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
endif()

########################################################################
#
# Compile and prepare library
#
########################################################################

add_subdirectory(cyme)
if(CYME_MAIN)
  add_subdirectory(sandbox/)
endif(CYME_MAIN)

########################################################################
#
# Tests
#
########################################################################

if(CYME_TESTS)
  include(CTest)
  enable_testing()
  add_subdirectory(tests)
endif(CYME_TESTS)

########################################################################
#
# install
#
########################################################################

set(GIT_DOCUMENTATION_REPO BBPDocumentation)
set(COMMON_ORGANIZATION_NAME BBP)
set(COMMON_PROJECT_DOMAIN ch.epfl.bluebrain)

set(DOXYGEN_CONFIG_FILE "${CMAKE_BINARY_DIR}/doc/Doxyfile")
set(DOXYGEN_BIB_FILES "cyme.bib")
file(COPY "${CMAKE_SOURCE_DIR}/doc/${DOXYGEN_BIB_FILES}" DESTINATION "${CMAKE_BINARY_DIR}/doc/")
configure_file("${CMAKE_SOURCE_DIR}/CMake/Doxyfile.in" "${DOXYGEN_CONFIG_FILE}" @ONLY)
include(DoxygenRule)
