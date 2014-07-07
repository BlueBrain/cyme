set(CYME_TEST_LIBRARIES ${Boost_LIBRARIES})
unset(CMAKE_RUNTIME_OUTPUT_DIRECTORY) #unset value to avoid pb

#check techno supported and give needed compil flag
function(compiler_flag testing_ techno_ test_ unroll_)
     STRING(REGEX REPLACE "^.*(sse).*$" "\\1" CYME_THERE ${techno_})
     STRING(COMPARE EQUAL "sse" "${CYME_THERE}" CYME_TRUE)
     IF (CYME_TRUE)
         set(simd_test "sse")
         set(flag "-msse4.1")
         test_arch_dependence(${testing_} "--account=proj16" ${flag} ${simd_test} ${unroll_} ${test_})
     endif (CYME_TRUE)

     STRING(REGEX REPLACE "^.*(avx).*$" "\\1" CYME_THERE ${techno_})
     STRING(COMPARE EQUAL "avx" "${CYME_THERE}" CYME_TRUE)
     IF (CYME_TRUE)
         set(simd_test "avx")
         set(flag  "-mavx")
         test_arch_dependence(${testing_} "--account=proj16" ${flag} ${simd_test} ${unroll_} ${test_})
     endif (CYME_TRUE)

     STRING(REGEX REPLACE "^.*(qpx).*$" "\\1" CYME_THERE ${techno_})
     STRING(COMPARE EQUAL "qpx" "${CYME_THERE}" CYME_TRUE)
     IF (CYME_TRUE)
         set(simd_test "qpx")
         test_arch_dependence(${testing_} "--account=proj16" " " ${simd_test} ${unroll_} ${test_})
         #no flag for BG/Q
     endif (CYME_TRUE)

     STRING(REGEX REPLACE "^.*(mic).*$" "\\1" CYME_THERE ${techno_})
     STRING(COMPARE EQUAL "mic" "${CYME_THERE}" CYME_TRUE)
     IF (CYME_TRUE)
         set(simd_test "mic")
         set(flag  "-mmic -D__FMA__")
         test_arch_dependence(${testing_} ${MIC_NATIVELOAD} ${flag} ${simd_test} ${unroll_} ${test_})
     endif (CYME_TRUE)

endfunction(compiler_flag)

#loop over tests
function(test_arch_dependence testing_ offload_ flag_ simd_ unroll_ test_)
    add_executable(${testing_}_${test_}_${simd_}_${unroll_} ${test_}.cpp)
    SET_TARGET_PROPERTIES(${testing_}_${test_}_${simd_}_${unroll_} PROPERTIES COMPILE_FLAGS "${flag_} -D__CYME_SIMD_VALUE__=${simd_} ${CYME_FMA_FLAGS} -D__CYME_UNROLL_VALUE__=${unroll_}")
    target_link_libraries(${testing_}_${test_}_${simd_}_${unroll_} ${Boost_LIBRARIES} ${CYME_TIME} ${CYME_MIC})
    if(SLURM_FOUND)
        add_test(NAME ${testing_}_${test_}_${simd_}_${unroll_} COMMAND ${SLURM_SRUN_COMMAND} ${offload_} ${testing_}_${test_}_${simd_}_${unroll_})
    else(SLURM_FOUND)
        add_test(${testing_}_${test_}_${simd_}_${unroll_} ${testing_}_${test_}_${simd_}_${unroll_})
    endif(SLURM_FOUND)
    if(${testing_} STREQUAL "ValidityTest")
        install(TARGETS ${testing_}_${test_}_${simd_}_${unroll_} RUNTIME DESTINATION lib/cyme/validity)
    endif()
endfunction(test_arch_dependence)

#add test directory
add_subdirectory (unit/memory)
add_subdirectory (unit/numeric)
add_subdirectory (validity/channels)
