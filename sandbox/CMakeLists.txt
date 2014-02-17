function(compil_flag techno_ main_)
     STRING(REGEX REPLACE "^.*(sse).*$" "\\1" CYME_THERE ${techno_})
     STRING(COMPARE EQUAL "sse" "${CYME_THERE}" CYME_TRUE)
     IF (CYME_TRUE)
         set(simd_test "sse")
         set(flag "-msse4.1")
         make_program(${main_} ${flag} "sse4.1")
     endif (CYME_TRUE)

     STRING(REGEX REPLACE "^.*(avx).*$" "\\1" CYME_THERE ${techno_})
     STRING(COMPARE EQUAL "avx" "${CYME_THERE}" CYME_TRUE)
     IF (CYME_TRUE)
         set(simd_test "avx")
         set(flag  "-mavx")
         make_program(${main_} ${flag} "avx1.0")
     endif (CYME_TRUE)
endfunction(compil_flag)

function(make_program main_ flag_ simd_)
    add_executable(${main_}_${simd_} ${main_}.cpp)
    SET_TARGET_PROPERTIES(${main_}_${simd_} PROPERTIES COMPILE_FLAGS "-D__CYME_SIMD_VALUE__=${SIMD_TECH} ${flag_} ${CYME_FMA_FLAGS}")
    target_link_libraries(${main_}_${simd_} ${Boost_CHRONO_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${CYME_TIME})
    target_link_libraries(${main_}_${simd_} ${Boost_CHRONO_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${CYME_TIME})
endfunction(make_program)

set(listmain main test_print)

foreach(test ${listmain})
    compil_flag(${SIMD_TECH} ${test})
endforeach()




