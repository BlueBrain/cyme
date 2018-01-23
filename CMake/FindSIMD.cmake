# Check if CYME instructions are available on the machine where
# the project is compiled.

macro(CYME_TECH_MATCH arg0 arg1)
    IF("${arg1}" MATCHES "${arg0}")
        set(CYME_TRUE "true")
    ELSE()
        set(CYME_TRUE "false")
    ENDIF()
endmacro()

macro(CYME_TECH_TRUE arg0)
    IF (CYME_TRUE)
       set(CYME_${arg0}_FOUND true CACHE BOOL "${arg0} available on host")
    ELSE (CYME_TRUE)
       MESSAGE(STATUS "Could not find hardware support for ${arg0} on this machine.")
    ENDIF (CYME_TRUE)
endmacro()

IF(BLUEGENE)
    IF(CYME_POWER_VMX)
        message("-- WARNING, You are on BG/Q front-end, but you are specifying VMX backend")
    ELSE()
        message("-- WARNING, You are on BG/Q front-end, QPX backend by default, please set up -DCYME_POWER_VMX=true for VMX backend")
    ENDIF()
ENDIF(BLUEGENE)

IF(CMAKE_SYSTEM_NAME MATCHES "Linux")
   EXEC_PROGRAM(cat ARGS "/proc/cpuinfo" OUTPUT_VARIABLE CPUINFO)
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Darwin")
   EXEC_PROGRAM("/usr/sbin/sysctl -n machdep.cpu.features" OUTPUT_VARIABLE CPUINFO1)
   string(TOLOWER ${CPUINFO1} CPUINFO1) #cmake regex are case sensitive
   EXEC_PROGRAM("/usr/sbin/sysctl -n machdep.cpu.leaf7_features" OUTPUT_VARIABLE CPUINFO2)
   string(TOLOWER ${CPUINFO2} CPUINFO2) #cmake regex are case sensitive
   set(CPUINFO "${CPUINFO1}" " " "${CPUINFO2}")
ENDIF(CMAKE_SYSTEM_NAME MATCHES "Linux")
#need quote for CPUINFO else the list is cut in two ... cmake mysteries
CYME_TECH_MATCH("sse4[._]1" "${CPUINFO}")
CYME_TECH_TRUE(SSE)

CYME_TECH_MATCH("avx" "${CPUINFO}")
CYME_TECH_TRUE(AVX)

CYME_TECH_MATCH("avx2" "${CPUINFO}")
CYME_TECH_TRUE(AVX2)

CYME_TECH_MATCH("asimd" "${CPUINFO}")
CYME_TECH_TRUE(NEON)

IF(CYME_POWER_VMX)
    CYME_TECH_MATCH(altivec "${CPUINFO}")
    CYME_TECH_TRUE(VMX)
ELSE(CYME_POWER_VMX)
    CYME_TECH_MATCH(altivec ${CPUINFO})
    if(CYME_TRUE AND BLUEGENE) #BGQ
        CYME_TECH_TRUE(QPX)
        MESSAGE(STATUS "Could not find hardware support for VMX on this machine.")
    elseif(CYME_TRUE AND NOT BLUEGENE)
        CYME_TECH_MATCH(altivec ${CPUINFO})
        CYME_TECH_TRUE(VMX)
    endif(CYME_TRUE AND BLUEGENE)
ENDIF(CYME_POWER_VMX)

if(NOT CYME_QPX_FOUND)
      MESSAGE(STATUS "Could not find hardware support for QPX on this machine.")
endif(NOT CYME_QPX_FOUND)

mark_as_advanced(CYME_SSE_FOUND CYME_AVX_FOUND CYME_AVX2_FOUND CYME_QPX_FOUND CYME_VMX_FOUND CYME_NEON_FOUND)
