#SET_TARGET_PROPERTIES(main PROPERTIES COMPILE_FLAGS "-stdlib=libc++ ")
add_executable(main main.cpp)
target_link_libraries(main  )
#target_link_libraries(main  -lrt)


add_executable(bench bench.cpp)
target_link_libraries(bench )
#target_link_libraries(bench -lrt)
