add_definitions (-DBOOST_TEST_DYN_LINK -Wno-unused-variable)

set(tests exp log vec)

if(${SIMD_TECH} STREQUAL "avx" OR ${SIMD_TECH} STREQUAL "sse" )
    set(simd_test sse avx)
endif()

if(${SIMD_TECH} STREQUAL "qpx")
    set(simd_test qpx)
endif()

if(${SIMD_TECH} STREQUAL "mic")
    set(simd_test mic)
endif()

foreach(simd ${simd_test})
    foreach(test ${tests})
        add_executable(${test}_test_${simd} ${test}.cpp)
        SET_TARGET_PROPERTIES(${test}_test_${simd} PROPERTIES COMPILE_FLAGS "-m${simd} -D__CYME_SIMD_VALUE__=${simd}") 
        target_link_libraries(${test}_test_${simd} ${Boost_LIBRARIES})
        add_test(${test}_test_${simd} ${test}_test_${simd} ) 
    endforeach(test)
endforeach(simd)
