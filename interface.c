// sudoku.c

#include <stdio.h>
#include "sudoku.h"

int board[ROW][COLUMN] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {9, 8, 7, 6, 5, 4, 3, 2, 1},
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {9, 8, 7, 6, 5, 4, 3, 2, 1},
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {9, 8, 7, 6, 5, 4, 3, 2, 1},
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {9, 8, 7, 6, 5, 4, 3, 2, 1},
        {1, 2, 3, 4, 5, 6, 7, 8, 9}
};

int display(int board[][COLUMN]) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    return 0;
}

