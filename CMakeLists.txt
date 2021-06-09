cmake_minimum_required(VERSION 3.17)
project(prg2 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra -Wconversion -Wsign-conversion -pedantic")

add_executable(prg2 main.c chapitre_1.c chapitre_2.c chapitre_3.c chapitre_4.c chapitre_5.c)
