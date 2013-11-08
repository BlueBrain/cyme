add_executable(main main.cpp)
add_definitions("-mavx -mfma -D__CYME_SIMD_VALUE__=${SIMD_TECH}")

set(LIBRAIRIES ${MASS_LIBRARY} ${SIMD_MASS_LIBRARY})

if(CYME_MATH)
    target_link_libraries(main ${LIBRAIRIES} ${Boost_CHRONO_LIBRARY}
${Boost_SYSTEM_LIBRARY} )
else(CYME_MATH)
    target_link_libraries(main  ${Boost_CHRONO_LIBRARY}
${Boost_SYSTEM_LIBRARY} )
endif(CYME_MATH)
