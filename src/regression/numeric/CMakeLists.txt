add_definitions (-DBOOST_TEST_DYN_LINK -Wno-unused-variable)

set(tests factorial pow exp vec)

foreach(test ${tests})
        add_executable(${test}_test ${test}.cpp)
        SET_TARGET_PROPERTIES(${test}_test PROPERTIES COMPILE_FLAGS "-DCYME_FUZZ_TESTS_ITERATIONS") 
        target_link_libraries(${test}_test ${Boost_LIBRARIES})
        add_test(${test}_test ${test}_test ) 
endforeach(test)
