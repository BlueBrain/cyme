function(compil_flag techno_ main_ unroll_)
     STRING(REGEX REPLACE "^.*(sse).*$" "\\1" CYME_THERE ${techno_})
     STRING(COMPARE EQUAL "sse" "${CYME_THERE}" CYME_TRUE)
     IF (CYME_TRUE)
         set(simd_test "sse")
         set(flag "-msse4.1")
         make_program(${main_} ${flag} "sse4.1" ${unroll_})
     endif (CYME_TRUE)

     STRING(REGEX REPLACE "^.*(avx).*$" "\\1" CYME_THERE ${techno_})
     STRING(COMPARE EQUAL "avx" "${CYME_THERE}" CYME_TRUE)
     IF (CYME_TRUE)
         set(simd_test "avx")
         set(flag  "-mavx")
         make_program(${main_} ${flag} "avx1.0" ${unroll_})
     endif (CYME_TRUE)

     STRING(REGEX REPLACE "^.*(chimera).*$" "\\1" CYME_THERE ${techno_})
     STRING(COMPARE EQUAL "chimera" "${CYME_THERE}" CYME_TRUE)
     IF (CYME_TRUE)
         set(simd_test "avx")
         set(flag  "-mavx")
         make_program(${main_} ${flag} "avx1.0" ${unroll_})
     endif (CYME_TRUE)


     STRING(REGEX REPLACE "^.*(qpx).*$" "\\1" CYME_THERE ${techno_})
     STRING(COMPARE EQUAL "qpx" "${CYME_THERE}" CYME_TRUE)
     IF (CYME_TRUE)
         set(simd_test "qpx")
         make_program(${main_} " " "qpx" ${unroll_})
     endif (CYME_TRUE)

     STRING(REGEX REPLACE "^.*(mic).*$" "\\1" CYME_THERE ${techno_})
     STRING(COMPARE EQUAL "mic" "${CYME_THERE}" CYME_TRUE)
     IF (CYME_TRUE)
         set(simd_test "mic")
         make_program(${main_} "-mmic -D__FMA__" "mic" ${unroll_})
     endif (CYME_TRUE)

endfunction(compil_flag)

function(make_program main_ flag_ simd_ unroll_)
    add_executable(${main_}_${simd_}_${unroll} ${main_}.cpp)
    SET_TARGET_PROPERTIES(${main_}_${simd_}_${unroll} PROPERTIES COMPILE_FLAGS
"-D__CYME_SIMD_VALUE__=${SIMD_TECH} -D__CYME_UNROLL_VALUE__=${unroll_} ${flag_} ${CYME_FMA_FLAGS}")
    target_link_libraries(${main_}_${simd_}_${unroll} ${Boost_CHRONO_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${CYME_TIME} ${CYME_MIC})
endfunction(make_program)

set(listunroll 1 2 4)
set(listmain main_c main_s test_print)

foreach(test ${listmain})
    foreach(unroll ${listunroll})
        compil_flag(${SIMD_TECH} ${test} ${unroll})
    endforeach()
endforeach()




