cmake_minimum_required(VERSION 4.3)
project(metodos_de_ordenacao C)

set(CMAKE_C_STANDARD 11)

add_executable(metodos_de_ordenacao
        main.c
        src/array.c
        src/export.c
        src/labels-filters.c
        src/menu.c
        src/metrics.c
        src/algoritmos/bubble-sort.c
        src/algoritmos/merge-sort.c
        src/algoritmos/quick-sort.c
        headers/array.h
        headers/export.h
        headers/labels-filters.h
        headers/menu.h
        headers/metrics.h
)

# Caminho do repositório, usado para exportar as métricas em resultados/metricas.csv
target_compile_definitions(metodos_de_ordenacao PRIVATE DIRETORIO_PROJETO="${CMAKE_SOURCE_DIR}")

add_compile_options("$<$<CXX_COMPILER_ID:GNU>:-finput-charset=UTF-8>" "$<$<CXX_COMPILER_ID:GNU>:-fexec-charset=UTF-8>")
