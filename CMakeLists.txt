cmake_minimum_required(VERSION 4.3)
project(metodos_de_ordenacao C)

set(CMAKE_C_STANDARD 11)

add_executable(metodos_de_ordenacao
        main.c
        src/core/array.c
        src/interface/labels-filters.c
        src/interface/menu.c
        src/metricas/exportacao.c
        src/metricas/metricas.c
        src/algoritmos/bubble-sort.c
        src/algoritmos/merge-sort.c
        src/algoritmos/quick-sort.c
)

target_include_directories(metodos_de_ordenacao
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/headers
)

# Caminho do repositório, usado para exportar as métricas em resultados/metricas.csv
target_compile_definitions(metodos_de_ordenacao PRIVATE DIRETORIO_PROJETO="${CMAKE_SOURCE_DIR}")

add_compile_options("$<$<CXX_COMPILER_ID:GNU>:-finput-charset=UTF-8>" "$<$<CXX_COMPILER_ID:GNU>:-fexec-charset=UTF-8>")
