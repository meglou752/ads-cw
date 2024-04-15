#include <stdio.h>
#include "sudoku.h"
#include <time.h>
int board[ROW][COLUMN] = {{0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0},};
int main()
{
    clock_t start_time, end_time;
    double cpu_time_used;
    start_time = clock();

    sudoku_helper(board, 0, 0);
    end_time = clock();
    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("CPU time used: %f seconds\n", cpu_time_used);

    display(board);
    return 0;
}