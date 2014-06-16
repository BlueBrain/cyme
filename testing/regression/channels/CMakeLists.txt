
set(unrolls 1 2 4)
#list tests
set(tests Na)

#loop over SIMD techno
foreach(techno ${SIMD_LIST_TEST})
    foreach(test ${tests})
        foreach(unroll ${unrolls})
           compiler_flag("RegressionTest" ${techno} ${test} ${unroll})
        endforeach()
    endforeach()
endforeach()
