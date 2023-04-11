cmake_minimum_required(VERSION 3.24)
project(dearchiver C)

set(CMAKE_C_STANDARD 11)

add_executable(dearchiver main.c decompressor.c decompressor.h)
