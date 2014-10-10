
add_library(cyme cyme.cpp)

if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "ppc64")
    set_target_properties(cyme PROPERTIES COMPILE_FLAGS "-D__CYME_SIMD_VALUE__=qpx -D__CYME_UNROLL_VALUE__=1 ${CYME_FMA_FLAGS}")
else()
    set_target_properties(cyme PROPERTIES COMPILE_FLAGS "-D__CYME_SIMD_VALUE__=sse -D__CYME_UNROLL_VALUE__=1 -msse4.1 ${CYME_FMA_FLAGS}")
endif()
