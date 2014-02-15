add_executable(main main.cpp)
add_executable(test_print test_print.cpp)

SET_TARGET_PROPERTIES(test_print PROPERTIES COMPILE_FLAGS "-D__CYME_SIMD_VALUE__=${SIMD_TECH} ${CYME_SIMD_FLAGS} ${CYME_FMA_FLAGS}")
SET_TARGET_PROPERTIES(main PROPERTIES COMPILE_FLAGS "-D__CYME_SIMD_VALUE__=${SIMD_TECH} ${CYME_SIMD_FLAGS} ${CYME_FMA_FLAGS}")

set(LIBRAIRIES ${MASS_LIBRARY} ${SIMD_MASS_LIBRARY})

if(CYME_MATH)
    target_link_libraries(main ${LIBRAIRIES} ${Boost_CHRONO_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${CYME_TIME})
    target_link_libraries(test_print ${LIBRAIRIES} ${Boost_CHRONO_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${CYME_TIME})
else(CYME_MATH)
    target_link_libraries(main ${Boost_CHRONO_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${CYME_TIME})
    target_link_libraries(test_print ${Boost_CHRONO_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${CYME_TIME})
endif(CYME_MATH)
