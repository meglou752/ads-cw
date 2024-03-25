#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "sudoku.h"

//can use the same validity checker for solution and player guess
int validity_check(int board[ROW][COLUMN], int row, int column, int num)
{
    int startRow = row - row%3;
    int startCol = column - column%3;

    for(int i = 0; i < ROW; i++)
    {
        if(board[row][i] == num)
        {
            return 0;
        }
    }
    for(int i = 0; i < COLUMN; i++)
    {
        if(board[i][column] == num)
        {
            return 0;
        }
    }
    for(int i = 0; i < 3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(board[i + startRow][j + startCol] == num)
            {
                return 0;
            }
        }
    }
    return 1;
}

int sudoku_helper(int puzzle[][9], int row, int column) {
            if (row == 9)
            {
                return 1;
            }
            else if(column == 9)
            {
                return sudokuHelper(puzzle, row + 1, 0);
            }
            else if(puzzle[row][column] != 0)
            {
                return sudokuHelper(puzzle, row, column+1);
            }
            else
            {
                for(int i = 0; i < 10; i++)
                {
                    if(validity_check(puzzle,row,column,i))
                    {
                        puzzle[row][column] = i;
                        if(sudokuHelper(puzzle,row,column+1))
                        {
                            return 1;
                        }
                        puzzle[row][column] = 0;
                    }
                }
                return 0;
            }
}
