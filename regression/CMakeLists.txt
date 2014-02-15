set(CYME_TEST_LIBRARIES ${Boost_LIBRARIES})

#check techno supported and give needed compil flag
function(compiler_flag techno_ test_)
     STRING(REGEX REPLACE "^.*(sse).*$" "\\1" CYME_THERE ${techno_})
     STRING(COMPARE EQUAL "sse" "${CYME_THERE}" CYME_TRUE)
     IF (CYME_TRUE)
         set(simd_test "sse")
         set(flag "-msse4.1")
         test_arch_dependence(${flag} ${simd_test} ${test_})
     endif (CYME_TRUE)

     STRING(REGEX REPLACE "^.*(avx).*$" "\\1" CYME_THERE ${techno_})
     STRING(COMPARE EQUAL "avx" "${CYME_THERE}" CYME_TRUE)
     IF (CYME_TRUE)
         set(simd_test "avx")
         set(flag  "-mavx")
         test_arch_dependence(${flag} ${simd_test} ${test_})
     endif (CYME_TRUE)
endfunction(compiler_flag)

#loop over tests
function(test_arch_dependence flag_ simd_ test_)
    add_executable(${test_}_test_${simd_} ${test_}.cpp)
    SET_TARGET_PROPERTIES(${test_}_test_${simd_} PROPERTIES COMPILE_FLAGS "${flag_} -D__CYME_SIMD_VALUE__=${simd_}" ${CYME_FMA_FLAGS})
    target_link_libraries(${test_}_test_${simd_} ${Boost_LIBRARIES} ${CYME_TIME})
    add_test(${test_}_test_${simd_} ${test_}_test_${simd_})
endfunction(test_arch_dependence)

#add test directory
add_subdirectory (memory)
add_subdirectory (numeric)
