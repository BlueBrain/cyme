#SET_TARGET_PROPERTIES(main PROPERTIES COMPILE_FLAGS "-stdlib=libc++ ")
#add_executable(main main.cpp)
#target_link_libraries(main  ${Boost_SYSTEM_LIBRARY_RELEASE} ${Boost_CHRONO_LIBRARY_RELEASE})

add_executable(mem mem.cpp)
target_link_libraries(mem  ${Boost_SYSTEM_LIBRARY_RELEASE} ${Boost_CHRONO_LIBRARY_RELEASE})
