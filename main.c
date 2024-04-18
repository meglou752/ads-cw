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
        initialise_board();
    }
    //display_board();

    end_time = clock();
    cpu_time_used = (((double) (end_time - start_time)) / CLOCKS_PER_SEC) / 10;

    printf("Average CPU time used for basic algorithm (3d array (pencilmarking), int data types): %f seconds\n", cpu_time_used);
    printf("\n");
    return 0;
}