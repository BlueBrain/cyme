set(CYME_TEST_LIBRARIES ${Boost_LIBRARIES})
unset(CMAKE_RUNTIME_OUTPUT_DIRECTORY) #unset value to avoid pb

add_custom_target(tests DEPENDS test)
set_target_properties(tests PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD ON)

#check techno supported and give needed compil flag
function(compiler_flag testing_ techno_ test_ unroll_)
#$ENV{SLURM_ACCOUNT} --account=proj16
     CYME_TECH_MATCH(sse ${techno_})
     IF (CYME_TRUE)
         test_arch_dependence(${testing_} "$ENV{SLURM_ACCOUNT}" "-msse4.1" "sse" ${unroll_} ${test_})
     endif ()

     CYME_TECH_MATCH(avx ${techno_})
     IF (CYME_TRUE)
         test_arch_dependence(${testing_} "$ENV{SLURM_ACCOUNT}" "-mavx" "avx" ${unroll_} ${test_})
     endif ()

     CYME_TECH_MATCH(neon ${techno_})
     IF (CYME_TRUE)
         test_arch_dependence(${testing_} "$ENV{SLURM_ACCOUNT}" "" "neon" ${unroll_} ${test_})
     endif ()

     CYME_TECH_MATCH(qpx ${techno_})
     IF (CYME_TRUE)
         test_arch_dependence(${testing_} "$ENV{SLURM_ACCOUNT}" " " "qpx" ${unroll_} ${test_})
         #no flag for BG/Q
     endif ()

     CYME_TECH_MATCH(vmx ${techno_})
     IF (CYME_TRUE)
         EXEC_PROGRAM(cat ARGS "/proc/cpuinfo" OUTPUT_VARIABLE CPUINFO)
         STRING(REGEX MATCH "POWER[7-8]" CYME_PROCESSOR ${CPUINFO} )
         string(TOLOWER ${CYME_PROCESSOR} CYME_PROCESSOR)
         set(flag  "-mcpu=${CYME_PROCESSOR} -maltivec -mvsx")
         test_arch_dependence(${testing_} "$ENV{SLURM_ACCOUNT}" ${flag} "vmx" ${unroll_} ${test_})
     endif ()

endfunction(compiler_flag)

#loop over tests
function(test_arch_dependence testing_ offload_ flag_ simd_ unroll_ test_)
    add_executable(${testing_}_${test_}_${simd_}_${unroll_} ${test_}.cpp)
    set_target_properties(${testing_}_${test_}_${simd_}_${unroll_} PROPERTIES COMPILE_FLAGS "${flag_} -D__CYME_SIMD_VALUE__=${simd_} ${CYME_FMA_FLAGS} -D__CYME_UNROLL_VALUE__=${unroll_}")
    target_link_libraries(${testing_}_${test_}_${simd_}_${unroll_} ${Boost_LIBRARIES} ${SIMD_SVML_LIBRARY} ${CYME_TIME} ${CYME_MIC})
    if(SLURM_FOUND)
        add_test(NAME ${testing_}_${test_}_${simd_}_${unroll_} COMMAND ${SLURM_SRUN_COMMAND} --time=00:03:00 ${testing_}_${test_}_${simd_}_${unroll_})
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
