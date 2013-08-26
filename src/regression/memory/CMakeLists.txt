add_definitions (-DBOOST_TEST_DYN_LINK -Wno-unused-variable)

set(tests alignment)
set(simd_test NORMAL SSE AVX QPXF QPXD)

foreach(test ${tests})
    foreach(simd ${simd_test})
        add_executable(${test}_${simd}_test ${test}.cpp)
        SET_TARGET_PROPERTIES(${test}_${simd}_test PROPERTIES COMPILE_FLAGS "-DVECTORIAL_SUPPORT=${simd}")
        target_link_libraries(${test}_${simd}_test ${Boost_LIBRARIES})
        add_test(${test}_${simd}_test ${test}_${simd}_test) 
    endforeach(simd)
endforeach(test)
