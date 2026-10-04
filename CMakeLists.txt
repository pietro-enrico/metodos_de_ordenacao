cmake_minimum_required(VERSION 4.3)
project(metodos_de_ordenacao C)

set(CMAKE_C_STANDARD 11)

add_executable(metodos_de_ordenacao
        src/bubble-sort.c
        src/merge-sort.c
        src/quick-sort.c
        main.c)
