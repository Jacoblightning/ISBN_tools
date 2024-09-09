cmake_minimum_required(VERSION 3.29)
project(ISBN_tools C)
include(CTest)

set(CMAKE_C_STANDARD 23)

add_executable(ISBN_tools main.c)

add_test(NAME TestAll COMMAND ../test.sh "${CMAKE_CURRENT_BINARY_DIR}/ISBN_tools")
