cmake_minimum_required(VERSION 3.14)
project(DaRefl VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

option(DAREFL_BUMP_VERSION "Propagate version number" OFF)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
include(configuration)

add_subdirectory(extern)
add_subdirectory(source)
add_subdirectory(tests)

# Defines new 'make clangformat' target to beautify whole code. See CodeTools.cmake for details.
#project_clangformat_setup()
