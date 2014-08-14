#add_definitions (-DBOOST_TEST_DYN_LINK -Wno-unused-variable)
add_definitions (-Wno-unused-variable)

set(tests exp log vec pow)
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
