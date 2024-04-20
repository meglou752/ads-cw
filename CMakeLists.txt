cmake_minimum_required(VERSION 3.27)
project(ADS C)

set(CMAKE_C_STANDARD 99)

add_executable(ADS main.c
        interface.c
        sudoku.h
        solver.c
        solver.h
        interface.h
        output_grid.c
        output_grid.h
        file_handling.c
        file_handling.h)
