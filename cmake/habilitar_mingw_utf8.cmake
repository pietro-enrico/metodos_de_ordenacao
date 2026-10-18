# MinGW Makefiles nao resolve caminhos com acentos (UTF-8): mingw32-make usa ACP ANSI.
# Antes de cada build, reescreve caminhos longos para a forma 8.3 (ASCII).

if(NOT WIN32)
  return()
endif()

if(NOT CMAKE_GENERATOR STREQUAL "MinGW Makefiles")
  return()
endif()

string(REGEX MATCH "[^ -~]" _METODOS_NON_ASCII "${CMAKE_SOURCE_DIR}")
if(NOT _METODOS_NON_ASCII)
  return()
endif()

message(STATUS "MinGW Makefiles: caminho UTF-8/acentos detectado — usando paths 8.3 (ASCII)")

if(NOT METODOS_REAL_MINGW_MAKE)
  set(METODOS_REAL_MINGW_MAKE "${CMAKE_MAKE_PROGRAM}" CACHE FILEPATH "mingw32-make original" FORCE)
endif()

# ShortPath via COM (Unicode) — cmd %~sI corrompe UTF-8 quando chamado pelo CMake
set(ENV{METODOS_PATH_FOR_SHORT} "${CMAKE_SOURCE_DIR}")
execute_process(
  COMMAND powershell -NoProfile -ExecutionPolicy Bypass -Command
          "(New-Object -ComObject Scripting.FileSystemObject).GetFolder($env:METODOS_PATH_FOR_SHORT).ShortPath"
  OUTPUT_VARIABLE _METODOS_SRC_SHORT
  OUTPUT_STRIP_TRAILING_WHITESPACE
  RESULT_VARIABLE _short_src_rc
  ERROR_VARIABLE _short_src_err
)
set(ENV{METODOS_PATH_FOR_SHORT} "${CMAKE_BINARY_DIR}")
execute_process(
  COMMAND powershell -NoProfile -ExecutionPolicy Bypass -Command
          "(New-Object -ComObject Scripting.FileSystemObject).GetFolder($env:METODOS_PATH_FOR_SHORT).ShortPath"
  OUTPUT_VARIABLE _METODOS_BIN_SHORT
  OUTPUT_STRIP_TRAILING_WHITESPACE
  RESULT_VARIABLE _short_bin_rc
  ERROR_VARIABLE _short_bin_err
)
unset(ENV{METODOS_PATH_FOR_SHORT})

if(NOT _short_src_rc EQUAL 0 OR NOT _short_bin_rc EQUAL 0 OR
   NOT _METODOS_SRC_SHORT OR NOT _METODOS_BIN_SHORT)
  message(WARNING "Falha ao obter caminho 8.3 (src=${_short_src_rc} bin=${_short_bin_rc}). Build MinGW pode falhar com acentos.")
  if(_short_src_err)
    message(WARNING "${_short_src_err}")
  endif()
  return()
endif()

message(STATUS "  source 8.3: ${_METODOS_SRC_SHORT}")
message(STATUS "  binary 8.3: ${_METODOS_BIN_SHORT}")

file(TO_CMAKE_PATH "${CMAKE_SOURCE_DIR}" _METODOS_SRC_LONG_CMAKE)
file(TO_CMAKE_PATH "${CMAKE_BINARY_DIR}" _METODOS_BIN_LONG_CMAKE)
file(TO_CMAKE_PATH "${_METODOS_SRC_SHORT}" _METODOS_SRC_SHORT_CMAKE)
file(TO_CMAKE_PATH "${_METODOS_BIN_SHORT}" _METODOS_BIN_SHORT_CMAKE)
file(TO_NATIVE_PATH "${CMAKE_SOURCE_DIR}" _METODOS_SRC_LONG_NATIVE)
file(TO_NATIVE_PATH "${CMAKE_BINARY_DIR}" _METODOS_BIN_LONG_NATIVE)

set(_METODOS_REAL_MAKE "${METODOS_REAL_MINGW_MAKE}")

configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/fix_mingw_utf8_paths.cmake.in"
  "${CMAKE_BINARY_DIR}/fix_mingw_utf8_paths.cmake"
  @ONLY
)

configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/mingw_make_wrapper.cmd.in"
  "${CMAKE_BINARY_DIR}/mingw_make_wrapper.bat"
  @ONLY
)

set(CMAKE_MAKE_PROGRAM "${CMAKE_BINARY_DIR}/mingw_make_wrapper.bat" CACHE FILEPATH "Wrapper MinGW paths ASCII/8.3" FORCE)
