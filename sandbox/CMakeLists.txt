function(compil_flag techno_ main_ unroll_)

     CYME_TECH_MATCH(sse ${techno_})
     IF (CYME_TRUE)
         make_program(${main_} "-msse4.1" "sse4.1" ${unroll_})
     endif()

     CYME_TECH_MATCH(avx ${techno_})
     IF (CYME_TRUE)
         make_program(${main_} "-mavx" "avx1.0" ${unroll_})
     endif ()

     CYME_TECH_MATCH(neon ${techno_})
     IF (CYME_TRUE)
         make_program(${main_} "" "neon" ${unroll_})
     endif ()

     CYME_TECH_MATCH(vmx ${techno_})
     IF (CYME_TRUE)
         EXEC_PROGRAM(cat ARGS "/proc/cpuinfo" OUTPUT_VARIABLE CPUINFO)
         STRING(REGEX MATCH "POWER[7-8]" CYME_PROCESSOR ${CPUINFO})
         string(TOLOWER ${CYME_PROCESSOR} CYME_PROCESSOR)
         set(flag  "-mcpu=${CYME_PROCESSOR} -maltivec -mvsx")
         make_program(${main_} ${flag} "vmx" ${unroll_})
     endif ()

     CYME_TECH_MATCH(qpx ${techno_})
     IF (CYME_TRUE)
         make_program(${main_} " " "qpx" ${unroll_})
     endif ()

endfunction(compil_flag)

function(make_program main_ flag_ simd_ unroll_)
    add_executable(${main_}_${simd_}_${unroll} ${main_}.cpp)
    SET_TARGET_PROPERTIES(${main_}_${simd_}_${unroll} PROPERTIES COMPILE_FLAGS "-D__CYME_SIMD_VALUE__=${SIMD_TECH} -D__CYME_UNROLL_VALUE__=${unroll_} ${flag_} ${CYME_FMA_FLAGS}")
    target_link_libraries(${main_}_${simd_}_${unroll} ${Boost_CHRONO_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${SIMD_SVML_LIBRARY} ${CYME_TIME} ${CYME_MIC})
endfunction(make_program)

set(listunroll 1 2 4)
set(listmain main_c test_print )
#set(listmain mandelbrot)

foreach(test ${listmain})
    foreach(unroll ${listunroll})
        compil_flag(${SIMD_TECH} ${test} ${unroll})
    endforeach()
endforeach()
