cmake_minimum_required(VERSION 3.7)
project(ls_c)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c directory.c directory.h)
add_executable(ls_c ${SOURCE_FILES})