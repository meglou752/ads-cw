#include "../Include/solver.h"

//int bot_nums_removed[HARD];


/**
 * Check validity of the current number to try in the specified coordinate by row, column, unit and pencil-mark state.
 * 3D array is utilised for pencilmarking for increased algorithm efficiency.
 * @param row Row coordinate for the current cell
 * @param column Column coordinate for the current cell
 * @param num Number to try in the current cell
 * @return 1 for valid placement; 0 for invalid placement
 */
int validity_check(int board[ROW][COLUMN][PENCILMARKS], int row, int column, int num) {
    int startRow = row - row % 3;
    int startCol = column - column % 3;

    for(int i = 0; i < ROW; i++) {
        if(board[row][i][0] == num) return 0; // Check row
    }

    for(int i = 0; i < COLUMN; i++) {
        if(board[i][column][0] == num) return 0; // Check column
    }

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i + startRow][j + startCol][0] == num) return 0; // Check unit
        }
    }

    if(board[row][column][num]) // Check pencil-mark
    {
        return 0;
    }

    return 1; // Valid placement
}

/**
 * Randomly shuffle an array of numbers of specified length
 * @param unit Array to be shuffled
 */
void shuffle(int unit[], int size) {
    int tmp;
    for(int i = 0; i < size; i++) {
        int random = rand() % size; // Generate random index, with param as upper constraint
        tmp = unit[i]; // Set the value in a temporary variable
        unit[i] = unit[random]; // Set the value to the random indexes number to swap with
        unit[random] = tmp; // Assign the initial index value to the randomly
    }
}

/**
 * Place randomly shuffled arrays along the diagonal units of the puzzle
 * @param board Board to seed units into
 */
void seed_random_units(int board[ROW][COLUMN][PENCILMARKS]) {
    int unit[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    srand(time(NULL)); // Seed random function

    int unit_index = 0;
    for (int i = 0; i < ROW; i += 3) {
        for (int j = 0; j < COLUMN; j += 3) {
            // If coord is 0,0 , 4,4 , or 7,7, place a shuffled array in current unit
            if (i == j) {
                unit_index = 0;
                shuffle(unit, 9);
                for (int u = 0; u < 3; u++) {
                    for (int v = 0; v < 3; v++) {
                        int num = unit[unit_index++];
                        board[i + u][j + v][0] = num; // Seed the number
                        board[i + u][j + v][num] = 1; // Mark the seeded number as tried
                    }
                }
            }
        }
    }
}

/**
 * Transverse through the board, trying for valid values 1-9 for each cell, until a valid solution is found
 * @param board Board to perform backtracking on
 * @param row Current row
 * @param column Current column
 * @return 1 for solved board; 0 for incomplete/invalid board
 */
int backtracking(int board[ROW][COLUMN][PENCILMARKS], int row, int column) {
    if (row == ROW) return 1; // Puzzle solved

    if (column == COLUMN) return backtracking(board, row + 1, 0);

    if (board[row][column][0] != 0) return backtracking(board, row, column + 1);

    for (int i = 1; i <= 9; i++) {
        if (board[row][column][i] != 1 && validity_check(board, row, column, i)) {
            board[row][column][0] = i; // Add value to board
            if (backtracking(board, row, column + 1)) return 1; // Puzzle solved
            board[row][column][0] = 0; // Reset value on the board
        }
    }
    return 0; // No valid number found for this cell, backtrack
}


/**
 * Transverse through the board, trying for valid values 9-1 for each cell, until a valid solution is found
 * @param board Board to perform backtracking on
 * @param row Current row
 * @param column Current column
 * @return 1 for solved board; 0 for incomplete/invalid board
 */
int reverse_backtracking(int board[ROW][COLUMN][PENCILMARKS], int row, int column) {
    if (row == ROW) return 1; // Puzzle solved

    if (column == COLUMN) return reverse_backtracking(board, row + 1, 0);

    if (board[row][column][0] != 0) return reverse_backtracking(board, row, column + 1);

    for (int i = 9; i >= 1; i--) { // Loop from 9 to 1
        if (board[row][column][i] != 1 && validity_check(board, row, column, i)) {
            board[row][column][0] = i; // Add value to board
            if (reverse_backtracking(board, row, column + 1)) return 1; // Puzzle solved
            board[row][column][0] = 0; // Reset value on the board
        }
    }
    return 0; // No valid number found for this cell, backtrack
}



/**
 * Duplicate 3d board to 3d board output variable
 * @param input Board to copy
 * @param output Board copied to
 */
void duplicate_board(int input[ROW][COLUMN][PENCILMARKS], int output[ROW][COLUMN][PENCILMARKS])
{
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COLUMN; j++) {
                output[i][j][0] = input[i][j][0];
            }
        }
}

/**
 * Function to generate random coordinates based on difficulty, time complexity O(n)
 * @param board 3D array representing the board to be edited
 * @param num_to_remove Numbers to be removed from the grid, depends on difficulty level
 */
void remove_numbers(int board[ROW][COLUMN][PENCILMARKS], int num_to_remove)
{
    // Declare and initialise array with nums 1-81
    int nums_to_remove[ROW*COLUMN];
    for(int i = 0; i < ROW*COLUMN; i++)
    {
        nums_to_remove[i] = i + 1;
    }

    shuffle(nums_to_remove, ROW*COLUMN); // Shuffle array

    for (int j = 0; j < num_to_remove; j++) // Loop through the amount of nums based on difficulty, preventing the same number being attempted multiple times
    {
        int x = (nums_to_remove[j] - 1) / ROW; // Calculate x coordinate
        int y = (nums_to_remove[j] - 1) % COLUMN; // Calculate y coordinate
        if(board == bot_solution_nums_removed)
        {
            for (int num = 0; num < HARD; num++)
            {
                // Store the numbers being removed, if handling bot grid, to enable random automated output with linear time complexity
                if(bot_nums_removed[num] == 0)
                {
                    bot_nums_removed[num] = nums_to_remove[num];
                    break;
                }
            }
        }
        board[x][y][0] = 0; // Set to 0 on the board
    }
}