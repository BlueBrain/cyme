set(APPTEST_PREFIX cyme_)

# test prefix making test namings unique automatically
set(TEST_PYTHON_BIN ${CMAKE_BINARY_DIR}/regression/python)

# configure and copy test python scripts to bin dir
file(GLOB UNIT_TEST_PYTHON_SOURCE_FILES *.py)
foreach(CURRENT ${UNIT_TEST_PYTHON_SOURCE_FILES})
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CURRENT} ${TEST_PYTHON_BIN})
endforeach(CURRENT)
configure_file(test.py ${TEST_PYTHON_BIN}/test.py)

# run all python tests
file(GLOB_RECURSE TEST_PYTHON_EXECUTABLE_FILES
    ${TEST_PYTHON_BIN}/*.py)
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES
    "${TEST_PYTHON_EXECUTABLE_FILES}")

foreach(CURRENT ${TEST_PYTHON_EXECUTABLE_FILES})
    string(REGEX REPLACE ".*/(.*)\\.py" "\\1" PREFIX "${CURRENT}")
    set(CURRENT_TEST_NAME ${APPTEST_PREFIX}${PREFIX})
    add_test(${CURRENT_TEST_NAME} ${PYTHON_EXECUTABLE} ${CURRENT})
endforeach(CURRENT)
