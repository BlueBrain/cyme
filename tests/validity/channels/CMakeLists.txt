
set(unrolls 1 2 4)
#list tests
set(tests Na)
set(files Na.cpp README helpers.hpp)

#loop over SIMD techno
foreach(test ${tests})
    foreach(techno ${SIMD_LIST_TEST})
        foreach(unroll ${unrolls})
           compiler_flag("ValidityTest" ${techno} ${test} ${unroll})
        endforeach()
    endforeach()
endforeach()
