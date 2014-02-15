add_executable(main main.cpp)
add_executable(test test.cpp)

add_definitions(-D__CYME_SIMD_VALUE__=${SIMD_TECH} ${CYME_SIMD_FLAGS})

set(LIBRAIRIES ${MASS_LIBRARY} ${SIMD_MASS_LIBRARY})

if(CYME_MATH)
    target_link_libraries(main ${LIBRAIRIES} ${Boost_CHRONO_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${CYME_TIME})
    target_link_libraries(test ${LIBRAIRIES} ${Boost_CHRONO_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${CYME_TIME})
else(CYME_MATH)
    target_link_libraries(main ${Boost_CHRONO_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${CYME_TIME})
    target_link_libraries(test ${Boost_CHRONO_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${CYME_TIME})
endif(CYME_MATH)
