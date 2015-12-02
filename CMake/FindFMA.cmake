# Check if CYME instructions are available on the machine where
# the project is compiled.

if(CYME_SSE_FOUND) # if sse supports FMA, avx supports it
     CYME_TECH_MATCH(fma ${CPUINFO})
     IF (CYME_TRUE)
        set(CYME_FMA_FOUND true)
     ELSE (CYME_TRUE)
        set(CYME_FMA_FOUND false)
     ENDIF (CYME_TRUE)
endif()

if(CYME_VMX_FOUND OR CYME_QPX_FOUND OR CYME_NEON_FOUND) #power/arm it is native
   set(CYME_FMA_FOUND true)
endif()

if(CYME_FMA_FOUND)
    set(CYME_FMA_FOUND true CACHE BOOL "FMA available on host")
else()
    set(CYME_FMA_FOUND false CACHE BOOL "FMA available on host")
endif()
