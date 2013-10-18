#SET_TARGET_PROPERTIES(main PROPERTIES COMPILE_FLAGS "-stdlib=libc++ ")
add_executable(main main.cpp)

set(LIBRAIRIES ${MASS_LIBRARY} ${SIMD_MASS_LIBRARY})

if(CYME_MATH)
    target_link_libraries(main ${LIBRAIRIES})
else(CYME_MATH)
    target_link_libraries(main  ${Boost_CHRONO_LIBRARY} ${Boost_SYSTEM_LIBRARY})
endif(CYME_MATH)

#add_executable(main_asm main.cpp)
#SET_TARGET_PROPERTIES(main_asm PROPERTIES COMPILE_FLAGS "-S ")
#target_link_libraries(main  -lrt)

#add_executable(bench bench.cpp)
#target_link_libraries(bench )
#target_link_libraries(bench -lrt)
