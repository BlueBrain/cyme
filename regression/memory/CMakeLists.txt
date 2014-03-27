#add_definitions (-DBOOST_TEST_DYN_LINK -Wno-unused-variable)
add_definitions (-Wno-unused-variable)

#list tests
set(tests alignment array array_algo vector serial)
set(unrolls 1 2 4)

#loop over SIMD techno
foreach(techno ${SIMD_LIST_TEST})
    #loop over test
    foreach(test ${tests})
        foreach(unroll ${unrolls})
            compiler_flag(${techno} ${test} ${unroll})
        endforeach()
    endforeach()
endforeach()
