cmake_minimum_required(VERSION 4.3)
project(metodos_de_ordenacao C)

set(CMAKE_C_STANDARD 11)

add_executable(metodos_de_ordenacao
        main.c
        src/array.c
        src/menu.c
        src/algoritmos/bubble-sort.c
        src/algoritmos/merge-sort.c
        src/algoritmos/quick-sort.c
        src/headers/array.h
        src/headers/menu.h
)

add_compile_options("$<$<CXX_COMPILER_ID:GNU>:-finput-charset=UTF-8>" "$<$<CXX_COMPILER_ID:GNU>:-fexec-charset=UTF-8>")
