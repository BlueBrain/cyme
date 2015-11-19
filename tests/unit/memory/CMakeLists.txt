#list tests
set(tests alignment array core_engine core_scalar vector serial gather_scatter)
set(unrolls 1 2 4)

#loop over SIMD techno
foreach(techno ${SIMD_LIST_TEST})
    #loop over test
    foreach(test ${tests})
        foreach(unroll ${unrolls})
            compiler_flag("UnitTest" ${techno} ${test} ${unroll})
        endforeach()
    endforeach()
endforeach()
