cmake_minimum_required(VERSION 3.29)
project(ISBN_Valid C)
include(CTest)

set(CMAKE_C_STANDARD 23)

add_executable(ISBN_Valid main.c)

add_test(NAME TestAll COMMAND test.sh)
set_tests_properties(TestAll PROPERTIES
        ARGS "${CMAKE_CURRENT_BINARY_DIR}/ISBN_tools"
)