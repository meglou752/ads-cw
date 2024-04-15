#include <stdio.h>
#include "sudoku.h"
#include <time.h>
#include <stdlib.h>

int main()
{
    srand(time(NULL));
    clock_t start_time, end_time;
    double cpu_time_used;
    start_time = clock();
    //seed_random_units();
    backtracking(0, 0);
    display_board();
    printf("\n");
    end_time = clock();
    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("CPU time used: %f seconds\n", cpu_time_used);
    printf("\n");

    return 0;
}
/*
 *     for(int i = 0; i < 3; i++)
    {
        seed_random_units(board,0,0, i);
    }
    backtracking(board, 0, 0);
    end_time = clock();
    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("CPU time used: %f seconds\n", cpu_time_used);

    display(board);
 */