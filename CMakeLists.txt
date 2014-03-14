#@author Ewart
#@date 2013-13-03
#@remarks Copyright BBP/EPFL 2005-2014; All rights reserved

cmake_minimum_required (VERSION 2.8)

# for SIMD detection
include(CheckCXXSourceCompiles)
include(CheckCXXCompilerFlag)
include(CheckCXXSourceRuns)

########################################################################
#
# Compiler information
#
########################################################################

if(MACHINE_CONFIG)
  if(EXISTS ${MACHINE_CONFIG})
    message(STATUS "Loading config in " ${MACHINE_CONFIG})
    include(${MACHINE_CONFIG})
  else(EXISTS ${MACHINE_CONFIG})
    message(ERROR " Machine config not found!")
  endif(EXISTS ${MACHINE_CONFIG})
endif(MACHINE_CONFIG)
set(CMAKE_INSTALL_PREFIX "/opt/cyme" CACHE STRING "Install path prefix, prepended onto install directories.")
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
if(NOT MACHINE_CONFIG)
    set(CMAKE_CXX_FLAGS_RELEASE "-Wall -DNDEBUG -O3" CACHE STRING "Compiler flags for Release compiles.")
    set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -O0 -m64" CACHE STRING "Compiler flags for Debug compiles.")
endif(NOT MACHINE_CONFIG)

########################################################################
#
# Project and version information
#
########################################################################

project (cyme)

set(RELEASE_VERSION OFF) # OFF or ABI version
set(LAST_RELEASE 0.9.0)
set(VERSION_MAJOR "1")
set(VERSION_MINOR "0")
set(VERSION_PATCH "0")

######################################################################
#
# CMake Modules Buildyard and description
#
######################################################################

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake
  ${CMAKE_SOURCE_DIR}/CMake/common)
include(GitExternal)

set(CYME_DESCRIPTION "SIMD computation over user cyme container")
set(COMMON_PROJECT_DOMAIN ch.epfl.bluebrain)
include(Common)
include(FindPackages)

set(Boost_USE_STATIC_LIBS ON) # to avoid conflict with common 

########################################################################
#
# options
#
########################################################################

option (CYME_MAIN "Build the main (sandbox)" ON)
option (CYME_TESTS "Build the CYMEE regression tests" OFF)
option (CYME_MATH "support lmass lmass_simd from IBM" OFF)
option (CYME_MIC_HOST "Check if MIC is install" OFF)

########################################################################
#
#  SIMD
#
########################################################################

find_package (SIMD)
find_package (FMA)
find_package (SLURM)

if(CYME_MIC_HOST)
   find_package (MIC)
endif(CYME_MIC_HOST)

if(MIC_NATIVE_FOUND)
   set(SIMD_TECH "mic" CACHE STRING "SIMD technology for the sandbox: sse, avx, qpx and mic")
   set(CYME_MIC "-mmic")
   set(SIMD_LIST_TEST "mic")
   set(SIMD_LIST_TESTING ${SIMD_LIST_TEST} CACHE STRING "SIMD technology for testing" )
else(MIC_NATIVE_FOUND)
   if(CYME_SSE4_1_FOUND)
   set(SIMD_TECH "sse" CACHE STRING "SIMD technology for the sandbox: sse, avx, qpx and mic")
   CHECK_CXX_COMPILER_FLAG("-msse4.1" SSE4_1_FLAG)
   if(SSE4_1_FLAG)
       SET(CMAKE_REQUIRED_FLAGS "-msse4.1")
       CHECK_CXX_SOURCE_COMPILES("#include <smmintrin.h> \n int main () {__m128d xmm; _mm_ceil_pd(xmm);};" SSE4_1_COMPILATION)
       CHECK_CXX_SOURCE_RUNS("#include <smmintrin.h> \n int main () {__m128d xmm; _mm_ceil_pd(xmm);};" SSE4_1_RUN)
       if(SSE4_1_FLAG AND SSE4_1_COMPILATION AND SSE4_1_RUN)
          set(CYME_SIMD_FLAGS "-msse4.1")
          set(SIMD_LIST_TEST "sse")
       else(SSE4_1_FLAG AND SSE4_1_COMPILATION AND SSE4_1_RUN)
          message(" -- Your machine does not support at least SSE 4.1, Cyme can not work")
       endif(SSE4_1_FLAG AND SSE4_1_COMPILATION AND SSE4_1_RUN)
   endif(SSE4_1_FLAG)
   endif(CYME_SSE4_1_FOUND)

   if(CYME_AVX1_0_FOUND)
   CHECK_CXX_COMPILER_FLAG("-mavx" AVX1_0_FLAG)
   if(AVX1_0_FLAG)
       SET(CMAKE_REQUIRED_FLAGS "-mavx")
       CHECK_CXX_SOURCE_COMPILES("#include <immintrin.h> \n int main () {__m256d xmm; _mm256_ceil_pd(xmm);};" AVX1_0_COMPILATION)
       CHECK_CXX_SOURCE_RUNS("#include <immintrin.h> \n int main () {__m256d xmm; _mm256_ceil_pd(xmm);};" AVX1_0_RUN)
       if(AVX1_0_FLAG AND AVX1_0_COMPILATION AND AVX1_0_RUN)
          set(CYME_SIMD_FLAGS "-mavx")
          set(SIMD_LIST_TEST ${SIMD_LIST_TEST} "avx")
          set(SIMD_LIST_TESTING ${SIMD_LIST_TEST} CACHE STRING "SIMD technology for testing" )
       endif(AVX1_0_FLAG AND AVX1_0_COMPILATION AND AVX1_0_RUN)
   endif(AVX1_0_FLAG)
   endif(CYME_AVX1_0_FOUND)
endif(MIC_NATIVE_FOUND)

if(CYME_QPX_FOUND)
   message("-- QPX supported")
   set(SIMD_TECH "qpx" CACHE STRING "SIMD technology for the sandbox: sse, avx, qpx and mic")
   set(SIMD_LIST_TEST "qpx")
   set(SIMD_LIST_TESTING ${SIMD_LIST_TEST} CACHE STRING "SIMD technology for testing" )
endif(CYME_QPX_FOUND)


if(CYME_FMA_FOUND)
    if(CYME_SSE4_1_FOUND)
        CHECK_CXX_COMPILER_FLAG("-mfma" FMA_FLAG)
        SET(CMAKE_REQUIRED_FLAGS "-msse4.1 -mfma")
        CHECK_CXX_SOURCE_COMPILES("#include <immintrin.h> \n int main () {__m128d xmm; _mm_fmadd_pd(xmm,xmm,xmm);};" FMA_COMPILATION)
        CHECK_CXX_SOURCE_RUNS("#include <immintrin.h> \n int main () {__m128d xmm; _mm_fmadd_pd(xmm,xmm,xmm);};" FMA_RUN)
        if(FMA_FLAG AND FMA_COMPILATION AND FMA_RUN)
           set(CYME_FMA_FLAGS "-mfma")
        endif(FMA_FLAG AND FMA_COMPILATION AND FMA_RUN)
    elseif(CYME_AVX1_0_FOUND)
        CHECK_CXX_COMPILER_FLAG("-mfma" FMA_FLAG)
        SET(CMAKE_REQUIRED_FLAGS "-mavx -mfma")
        CHECK_CXX_SOURCE_COMPILES("#include <immintrin.h> \n int main () {__m256d xmm; _mm256_fmadd_pd(xmm,xmm,xmm);};" FMA_COMPILATION)
        CHECK_CXX_SOURCE_RUNS("#include <immintrin.h> \n int main () {__m256d xmm; _mm256_fmadd_pd(xmm,xmm,xmm);};" FMA_RUN)
        if(FMA_FLAG AND FMA_COMPILATION AND FMA_RUN)
           set(CYME_FMA_FLAGS "-mfma")
        endif(FMA_FLAG AND FMA_COMPILATION AND FMA_RUN)
    elseif(CYME_QPX_FOUND)
           message("-- FMA supported")
           set(CYME_FMA_FLAGS "-D__FMA__")
    endif(CYME_SSE4_1_FOUND)
endif(CYME_FMA_FOUND)

########################################################################
#
#
########################################################################

include_directories ("${PROJECT_SOURCE_DIR}/cyme")

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
# Find BOOST dependencies
#
########################################################################

#set(Boost_NO_SYSTEM_PATHS TRUE)
set(BOOST_MIN_VERSION "1.49.0")
find_package (Boost ${BOOST_MIN_VERSION} REQUIRED unit_test_framework system chrono)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

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
include_directories ("${PROJECT_BINARY_DIR}")
include_directories ("${PROJECT_SOURCE_DIR}")

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
    add_subdirectory (regression)
endif(CYME_TESTS)

########################################################################
#
# install
#
########################################################################

install(DIRECTORY cyme DESTINATION include FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp" PATTERN "*.ipp")

include(CPackConfig)
include(DoxygenRule)
