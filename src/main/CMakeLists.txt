#SET_TARGET_PROPERTIES(main PROPERTIES COMPILE_FLAGS "-stdlib=libc++ ")
#add_executable(main main.cpp)
#target_link_libraries(main  ${Boost_SYSTEM_LIBRARY_RELEASE} ${Boost_CHRONO_LIBRARY_RELEASE})

#add_executable(exp exp.cpp)
#target_link_libraries(exp  ${Boost_SYSTEM_LIBRARY_RELEASE} ${Boost_CHRONO_LIBRARY_RELEASE})

#add_executable(mul mul.cpp)
#target_link_libraries(mul  ${Boost_SYSTEM_LIBRARY_RELEASE} ${Boost_CHRONO_LIBRARY_RELEASE})

add_executable(bench bench.cpp)
target_link_libraries(bench  ${Boost_SYSTEM_LIBRARY_RELEASE} ${Boost_CHRONO_LIBRARY_RELEASE})
