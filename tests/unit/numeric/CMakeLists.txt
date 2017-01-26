#add_definitions (-DBOOST_TEST_DYN_LINK -Wno-unused-variable)
add_definitions (-Wno-unused-variable)

if(CYME_TRIGO)
set(tests exp exp2 exp10 log log2 log10 vec pow sqrt fabs sin cos tan)
else()
set(tests exp exp2 exp10 log log2 log10 vec pow sqrt fabs bitwise)
endif()


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
