#include <stdio.h>
#include "sudoku.h"
int main()
{
    int board[ROW][COLUMN] = {0};
    sudokuHelper(board, 0, 0);
    display(board);
    return 0;
}