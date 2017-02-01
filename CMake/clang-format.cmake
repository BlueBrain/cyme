# additional target to perform clang-format run, requires clang-format

# Adding clang-format target if executable is found
find_program(CLANG_FORMAT "clang-format")
# Adding clang-tidy a lot of tool to improove the quality of the code
find_program(CLANG_TIDY "clang-tidy")
# Get all project files

if(CLANG_FORMAT)
  add_custom_target(
    format
    #we specify the 3 directories directly to avoid to parse the build repo
    COMMAND CLANG_FORMAT=clang-format ${PROJECT_SOURCE_DIR}/CMake/format_files.sh ${PROJECT_SOURCE_DIR}/cyme
    COMMAND CLANG_FORMAT=clang-format ${PROJECT_SOURCE_DIR}/CMake/format_files.sh ${PROJECT_SOURCE_DIR}/tests
    COMMAND CLANG_FORMAT=clang-format ${PROJECT_SOURCE_DIR}/CMake/format_files.sh ${PROJECT_SOURCE_DIR}/sandbox
    )
endif()

