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
    for(int i = 0; i < 1000; i++)
    {
        seed_random_units();
        backtracking(0, 0);
    }

    //display_board();
    end_time = clock();
    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Average CPU time, based on 1000 iterations, for basic algorithm (2d array, int data types): %f seconds\n", cpu_time_used);
    return 0;
}
