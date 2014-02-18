#add_definitions (-DBOOST_TEST_DYN_LINK -Wno-unused-variable)
add_definitions (-Wno-unused-variable)

set(tests exp log vec)

#loop over SIMD techno
foreach(techno ${SIMD_LIST_TEST})
    #loop over test
    foreach(test ${tests})
        compiler_flag(${techno} ${test})
    endforeach()
endforeach()
