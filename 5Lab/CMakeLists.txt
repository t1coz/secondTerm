cmake_minimum_required(VERSION 3.25)
project(5Lab C)

set(CMAKE_C_STANDARD 11)

add_executable(5Lab main.c menuCommands.c menuCommands.h cache.h cache.c functionsForFile.c functionsForFile.h)
