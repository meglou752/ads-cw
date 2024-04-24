cmake_minimum_required(VERSION 3.27)
project(ADS C)

set(CMAKE_C_STANDARD 99)

add_executable(ADS main.c
        Presentation/interface.c
        Include/sudoku.h
        Business/solver.c
        Include/solver.h
        Include/interface.h
        Business/output_grid.c
        Include/output_grid.h
        Data/file_handling.c
        Include/file_handling.h)
