// sudoku.c

#include <stdio.h>
#include "sudoku.h"

void main_menu()
{

}

int display(int board[][COLUMN]) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    return 0;
}

