add_definitions (-DBOOST_TEST_DYN_LINK -Wno-unused-variable)

#list tests
set(tests alignment array array_algo vector serial)

#loop over SIMD techno
foreach(techno ${SIMD_LIST_TEST})
    #loop over test
    foreach(test ${tests})
        compiler_flag(${techno} ${test})
    endforeach()
endforeach()
