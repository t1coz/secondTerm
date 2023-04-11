cmake_minimum_required(VERSION 3.24)
project(archiver C)

set(CMAKE_C_STANDARD 99)

add_executable(archiver main.c functions.c words.h functionsForWords.c functionsForWords.h)
