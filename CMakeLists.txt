cmake_minimum_required(VERSION 4.3)
project(metodos_de_ordenacao C)

set(CMAKE_C_STANDARD 11)

# MinGW Makefiles + caminho com acentos (UTF-8): normaliza paths antes do make
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/habilitar_mingw_utf8.cmake")

add_executable(metodos_de_ordenacao
        main.c
        src/core/array.c
        src/interface/formatacao-rotulos.c
        src/interface/menu.c
        src/metricas/exportacao.c
        src/metricas/metricas.c
        src/algoritmos/bubble-sort.c
        src/algoritmos/merge-sort.c
        src/algoritmos/quick-sort.c
        src/algoritmos/bubble-sort.c
        src/algoritmos/bubble-sort.c
)

target_include_directories(metodos_de_ordenacao
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/headers
)

# Caminho do repositório em UTF-8 (exportacao.c converte para UTF-16 no Windows)
target_compile_definitions(metodos_de_ordenacao PRIVATE DIRETORIO_PROJETO="${CMAKE_SOURCE_DIR}")

# Charset UTF-8 no GCC (projeto C — usar C_COMPILER_ID, nao CXX)
add_compile_options("$<$<C_COMPILER_ID:GNU>:-finput-charset=UTF-8>" "$<$<C_COMPILER_ID:GNU>:-fexec-charset=UTF-8>")