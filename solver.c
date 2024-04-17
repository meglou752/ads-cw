#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "sudoku.h"

int board[ROW][COLUMN][PENCILMARKS];

//can use the same validity checker for solution and player guess
int validity_check(int board[ROW][COLUMN][PENCILMARKS], int row, int column, int num)
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
    for(int i = 0; i < UNIT_ROW; i++)
    {
        for(int j=0; j< UNIT_COL; j++)
        {
            if(board[i + startRow][j + startCol] == num)
            {
                return 0;
            }
        }
    }
    for(int i = 0; i < PENCILMARKS; i++)
    {
        if(board[row][column][i--] == 0)
        {
            return 0;
        }
    }
    return 1;
}

void shuffle(int unit[])
{
    int tmp;
    for(int i = 0; i < 9; i++)
    {
            int random = (rand() % 9);
            tmp = unit[i];
            unit[i] = unit[random];
            unit[random] = tmp;
    }
}

void seed_random_units() {
    // Initialize array containing numbers 1 to 9
    int unit[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Shuffle the array
    srand(time(NULL));
    shuffle(unit);

    // Seed each 3x3 unit along the main diagonal of the puzzle with shuffled numbers
    int k = 0; // Index for the shuffled array
    for (int i = 0; i < ROW; i += 3) {
        for (int j = 0; j < COLUMN; j += 3) {
            if (i == j) { // Seed along the main diagonal 0,0, 4,4, 7,7
                k=0;
                for (int u = 0; u < 3; u++) {
                    for (int v = 0; v < 3; v++) {
                        board[i + u][j + v][0] = unit[k++];
                        board[i + u][j + v][unit[k-1]] = 1;
                    }
                }
            }
        }
    }
}


int backtracking(int row, int column) {
            if (row == ROW)
            {
                return 1;
            }
            else if(column == COLUMN)
            {
                return backtracking(row + 1, 0);
            }
            else if(board[row][column][0] != 0)
            {
                return backtracking(row, column+1);
            }
            else
            {
                for(int i = 0; i < PENCILMARKS; i++)
                {
                    if(validity_check(board,row,column,i--))
                    {
                        board[row][column][0] = i;
                        board[row][column][i] = 1;
                        if(backtracking(row,column+1))
                        {
                            return 1;
                        }
                        board[row][column][0] = 0;
                        board[row][column][i] = 0;
                    }
                }
                return 0;
            }
}

void display_board() {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            printf("%d \0", board[i][j]);
        }
        printf("\n");
    }
}