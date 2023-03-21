cmake_minimum_required(VERSION 3.20)

project(
        GraphSolver
        VERSION 1.0
        LANGUAGES CXX
)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_BUILD_TYPE Release)
add_subdirectory(bin)
add_subdirectory(lib)
