# Check if CYME instructions are available on the machine where
# the project is compiled.



IF(CMAKE_SYSTEM_NAME MATCHES "Linux")
   EXEC_PROGRAM(cat ARGS "/proc/cpuinfo" OUTPUT_VARIABLE CPUINFO)

   STRING(REGEX REPLACE "^.*(sse4_1).*$" "\\1" CYME_THERE ${CPUINFO})
   STRING(COMPARE EQUAL "sse4_1" "${CYME_THERE}" CYME_TRUE)
   IF (CYME_TRUE)
      set(CYME_SSE4_1_FOUND true CACHE BOOL "SSE 4.1 available on host")
   ELSE (CYME_TRUE)
      set(CYME_SSE4_1_FOUND false CACHE BOOL "SSE 4.1 available on host")
   ENDIF (CYME_TRUE)

   STRING(REGEX REPLACE "^.*(avx).*$" "\\1" CYME_THERE ${CPUINFO})
   STRING(COMPARE EQUAL "avx" "${CYME_THERE}" CYME_TRUE)
   IF (CYME_TRUE)
      set(CYME_AVX1_0_FOUND true CACHE BOOL "AVX 1.0 available on host")
   ELSE (CYME_TRUE)
      set(CYME_AVX1_0_FOUND false CACHE BOOL "AVX 1.0 available on host")
   ENDIF (CYME_TRUE)

   STRING(REGEX REPLACE "^.*(POWER7).*$" "\\1" CYME_THERE ${CPUINFO})
   STRING(COMPARE EQUAL "POWER7" "${CYME_THERE}" CYME_TRUE)
   IF (CYME_TRUE)
      set(CYME_QPX_FOUND true CACHE BOOL "QPX available on host")
   ELSE (CYME_TRUE)
      set(CYME_QPX_FOUND false CACHE BOOL "QPX available on host")
   ENDIF (CYME_TRUE)
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Darwin")
   EXEC_PROGRAM("/usr/sbin/sysctl -n machdep.cpu.features" OUTPUT_VARIABLE
      CPUINFO)

   STRING(REGEX REPLACE "^.*(SSE4).*$" "\\1" CYME_THERE ${CPUINFO})
   STRING(COMPARE EQUAL "SSE4" "${CYME_THERE}" CYME_TRUE)
   IF (CYME_TRUE)
      set(CYME_SSE4_1_FOUND true CACHE BOOL "SSE 4.1 available on host")
   ELSE (CYME_TRUE)
      set(CYME_SSE4_1_FOUND false CACHE BOOL "SSE 4.1 available on host")
   ENDIF (CYME_TRUE)

   STRING(REGEX REPLACE "^.*(AVX1).*$" "\\1" CYME_THERE ${CPUINFO})
   STRING(COMPARE EQUAL "AVX1" "${CYME_THERE}" CYME_TRUE)
   IF (CYME_TRUE)
      set(CYME_AVX1_0_FOUND true CACHE BOOL "AV 1.0 available on host")
   ELSE (CYME_TRUE)
      set(CYME_AVX1_0_FOUND false CACHE BOOL "AVX 1.0 available on host")
   ENDIF (CYME_TRUE)

ENDIF(CMAKE_SYSTEM_NAME MATCHES "Linux")

if(NOT CYME_SSE4_1_FOUND)
      MESSAGE(STATUS "Could not find hardware support for SSE 4.1 on this machine.")
endif(NOT CYME_SSE4_1_FOUND)

if(NOT CYME_AVX1_0_FOUND)
      MESSAGE(STATUS "Could not find hardware support for AVX on this machine.")
endif(NOT CYME_AVX1_0_FOUND)

if(NOT CYME_QPX_FOUND)
      MESSAGE(STATUS "Could not find hardware support for QPX on this machine.")
endif(NOT CYME_QPX_FOUND)

mark_as_advanced(CYME_SSE4_1_FOUND CYME_AVX1_0_FOUND CYME_QPX_FOUND)
