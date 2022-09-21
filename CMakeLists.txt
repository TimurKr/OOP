cmake_minimum_required(VERSION 3.20)
project(OOP C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(src)

add_executable(OOP
        src/main.c)
