cmake_minimum_required(VERSION 4.3)
project(metodos_de_ordenacao C)

set(CMAKE_C_STANDARD 11)

add_executable(metodos_de_ordenacao
        main.c
        src/menu.c
        src/algoritmos/bubble-sort.c
        src/algoritmos/merge-sort.c
        src/algoritmos/quick-sort.c
)