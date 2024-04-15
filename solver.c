#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "sudoku.h"

int board[ROW][COLUMN] = {{0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0},};
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

int shuffle(int unit[])
{
    int tmp;
    for(int i = 0; i < 9; i++)
    {
            int random = (rand() % 9);
            tmp = unit[i];
            unit[i] = unit[random];
            unit[random] = tmp;
    }
    return 0;
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
            if (i == j) { // Seed along the main diagonal
                for (int u = 0; u < 3; u++) {
                    for (int v = 0; v < 3; v++) {
                        board[i + u][j + v] = unit[k++];
                    }
                }
            }
        }
    }
}


int backtracking(int row, int column) {
            if (row == 9)
            {
                return 1;
            }
            else if(column == 9)
            {
                return backtracking(row + 1, 0);
            }
            else if(board[row][column] != 0)
            {
                return backtracking(row, column+1);
            }
            else
            {
                for(int i = 0; i < 10; i++)
                {
                    if(validity_check(board,row,column,i))
                    {
                        board[row][column] = i;
                        if(backtracking(row,column+1))
                        {
                            return 1;
                        }
                        board[row][column] = 0;
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