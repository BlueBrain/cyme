# Check if CYME instructions are available on the machine where 
# the project is compiled.

IF(CMAKE_SYSTEM_NAME MATCHES "Linux")
   EXEC_PROGRAM(cat ARGS "/proc/cpuinfo" OUTPUT_VARIABLE CPUINFO)

   STRING(REGEX REPLACE "^.*(fma).*$" "\\1" CYME_THERE ${CPUINFO})
   STRING(COMPARE EQUAL "fma" "${CYME_THERE}" CYME_TRUE)
   IF (CYME_TRUE)
      set(CYME_FMA_FOUND_X true)
   ELSE (CYME_TRUE)
      set(CYME_FMA_FOUND_X false)
   ENDIF (CYME_TRUE)

   STRING(REGEX REPLACE "^.*(POWER7).*$" "\\1" CYME_THERE ${CPUINFO})
   STRING(COMPARE EQUAL "POWER7" "${CYME_THERE}" CYME_TRUE)
   IF (CYME_TRUE)
      set(CYME_FMA_FOUND_P true)
   ELSE (CYME_TRUE)
      set(CYME_FMA_FOUND_P false)
   ENDIF (CYME_TRUE)


ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Darwin")
   EXEC_PROGRAM("/usr/sbin/sysctl -n machdep.cpu.features" OUTPUT_VARIABLE CPUINFO)

   STRING(REGEX REPLACE "^.*(FMA).*$" "\\1" CYME_THERE ${CPUINFO})
   STRING(COMPARE EQUAL "FMA" "${CYME_THERE}" CYME_TRUE)
   IF (CYME_TRUE)
      set(CYME_FMA_FOUND_X true)
   ELSE (CYME_TRUE)
      set(CYME_FMA_FOUND_X false)
   ENDIF (CYME_TRUE)
ENDIF(CMAKE_SYSTEM_NAME MATCHES "Linux")


IF (CYME_FMA_FOUND_X)
   set(__FMA__ true)
   set(CYME_FMA_FOUND true CACHE BOOL "FMA available on host")
   ELSEIF(CYME_FMA_FOUND_P)
      set(CYME_FMA_FOUND true CACHE BOOL "FMA available on host")
    ELSE ( CYME_FMA_FOUND_X)
      set(CYME_FMA_FOUND false CACHE BOOL "FMA available on host")
ENDIF(CYME_FMA_FOUND_X)

if(NOT CYME_FMA_FOUND)
      MESSAGE(STATUS "Could not find hardware support for FMA on this machine.")
endif(NOT CYME_FMA_FOUND)

mark_as_advanced(CYME_FMA_FOUND)
