#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "sudoku.h"

//can use the same validity checker for solution and player guess
bool validity_check(int board[ROW][COLUMN], int row, int column, int num)
{
    int startRow = row - row%3;
    int startCol = column - column%3;

    for(int i = 0; i < ROW; i++)
    {
        if(board[row][i] == num)
        {
            return false;
        }
    }
    for(int i = 0; i < COLUMN; i++)
    {
        if(board[i][column] == num)
        {
            return false;
        }
    }
    for(int i = 0; i < 3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(board[i + startRow][j + startCol] == num)
            {
                return false;
            }
        }
    }
    return true;
}

int sudokuHelper(int puzzle[][9], int row, int column) {
    //for num one through 9
    for(int i = 1; i < 10; i++)
    {
        if(validity_check(puzzle, row, column, i))
        {
            puzzle[row][column] = i;
            int nextRow, nextCol;
            if(column == 8)
            {
                nextCol = 0;
                nextRow = row + 1;
            }
            else
            {
                nextRow = row;
                nextCol = column + 1;
            }
            if(nextRow == 9)
            {
                return 1; //base case reached
            }
            if(sudokuHelper(puzzle, nextRow, nextCol))
            {
                return 1;
            }
            puzzle[row][column] = 0;
        }
    }
    return 0;
}
