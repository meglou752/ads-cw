#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// Define the Sudoku board dimensions
#define ROW 9
#define COLUMN 9

// Global Sudoku board
char board[ROW][COLUMN];

// Function to check the validity of placing a number at a certain position on the board
int validity_check(int row, int column, char num)
{
    int startRow = row - row % 3;
    int startCol = column - column % 3;

    // Check row and column
    for(int i = 0; i < ROW; i++)
    {
        if(board[row][i] == num || board[i][column] == num)
        {
            return 0; // Invalid placement
        }
    }

    // Check 3x3 subgrid
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i + startRow][j + startCol] == num)
            {
                return 0; // Invalid placement
            }
        }
    }
    return 1; // Valid placement
}

// Function to shuffle an array of integers
void shuffle(int unit[])
{
    int tmp;
    for(int i = 0; i < 9; i++)
    {
        int random = rand() % 9;
        tmp = unit[i];
        unit[i] = unit[random];
        unit[random] = tmp;
    }
}

// Function to seed random numbers in each 3x3 unit along the main diagonal of the puzzle
void seed_random_units() {
    // Initialize array containing numbers 1 to 9
    int unit[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Shuffle the array
    srand(time(NULL));

    // Seed each 3x3 unit along the main diagonal of the puzzle with shuffled numbers
    int k = 0; // Index for the shuffled array
    for (int i = 0; i < ROW; i += 3) {
        for (int j = 0; j < COLUMN; j += 3) {
            if (i == j) { // Seed along the main diagonal
                k = 0;
                shuffle(unit);
                for (int u = 0; u < 3; u++) {
                    for (int v = 0; v < 3; v++) {
                        board[i + u][j + v] = unit[k++] + '0';
                    }
                }
            }
        }
    }
}

// Function to solve the Sudoku puzzle using backtracking algorithm
int backtracking(int row, int column) {
    if (row == 9)
    {
        return 1; // Puzzle solved
    }
    else if(column == 9)
    {
        return backtracking(row + 1, 0);
    }
    else if(board[row][column] != '0')
    {
        return backtracking(row, column + 1);
    }
    else
    {
        for(int i = 1; i <= 9; i++) // Try placing numbers 1 to 9
        {
            if(validity_check(row, column, i + '0'))
            {
                board[row][column] = i + '0';
                if(backtracking(row, column + 1))
                {
                    return 1; // Puzzle solved
                }
                board[row][column] = '0'; // Backtrack
            }
        }
        return 0; // No valid number found for this cell
    }
}

// Function to display the Sudoku board
void display_board() {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void initialise_board()
{
    seed_random_units();
    backtracking(0,0);
    display_board();
}