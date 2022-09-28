cmake_minimum_required(VERSION 3.23)
project(C_Matrix C)

set(CMAKE_C_STANDARD 17)

include_directories(inc)
file(GLOB_RECURSE SOURCES "src/*.*")

add_executable(C_Matrix main.c ${SOURCES})
