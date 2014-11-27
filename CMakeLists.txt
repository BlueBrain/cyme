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

option(CYME_BUILDYARD "Build with Buildyard"  ON)
set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE STRING "Build architectures for OS X" FORCE) #overwrite Builyard setting 32 bit is outdated

set(LAST_RELEASE 1.0.0)
set(VERSION_MAJOR "1")
set(VERSION_MINOR "1")
set(VERSION_PATCH "0")
set(VERSION_ABI "1")

######################################################################
#
# CMake Modules Buildyard and description
#
######################################################################
set(CYME_DESCRIPTION "SIMD computation over user cyme container")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake ${CMAKE_SOURCE_DIR}/CMake/common)

# some common set up of two version
set(Boost_USE_STATIC_LIBS ON) # to avoid conflict with common 
set(BOOST_MIN_VERSION "1.49.0") #old is bad

set(COMMON_USE_CXX03 "ON" CACHE STRING "C++11 features are disabled " FORCE)
include(GitExternal)
set(COMMON_PROJECT_DOMAIN ch.epfl.bluebrain)
include(Common)
include(FindPackages)

########################################################################
#
# options
#
########################################################################

option (CYME_MAIN "Build the main (sandbox)" ON)
option (CYME_LIBRARY "Build a library for serial computation" ON)
option (CYME_TESTS "Build the CYMEE regression tests" ON)
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

#boost test has a dependency with system time
IF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(CYME_TIME "-lrt")
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(CYME_TIME) #nothing
ENDIF(CMAKE_SYSTEM_NAME MATCHES "Linux")

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
    add_subdirectory (test)
endif(CYME_TESTS)

########################################################################
#
# install
#
########################################################################

set(GIT_DOCUMENTATION_REPO BBPDocumentation)
set(COMMON_ORGANIZATION_NAME BBP)
set(COMMON_PROJECT_DOMAIN ch.epfl.bluebrain)
include(DoxygenRule)
include(CPackConfig)
