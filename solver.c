#include "solver.h"

int solution[ROW][COLUMN][PENCILMARKS] = {{{0}}};
 int solution_playable[ROW][COLUMN][PENCILMARKS] = {{{0}}};
int solution_numbers_removed[ROW][COLUMN][PENCILMARKS] = {{{0}}};

/**
 * Generate a solution
 */
void initialise_board(int num_to_remove) {
    seed_random_units();
    backtracking(0, 0);
    duplicate_board('o', solution_numbers_removed);
    remove_numbers(num_to_remove);
}


/**
 * Check validity of the current number to try in the specified coordinate by row, column, unit and pencilmark state.
 * 3D array is utilised for pencilmarking for increased algorithm efficiency.
 * @param row Row coordinate for the current cell
 * @param column Column coordinate for the current cell
 * @param num Number to try in the current cell
 * @return 1 for valid placement; 0 for invalid placement
 */
int validity_check(int row, int column, int num) {
    int startRow = row - row % 3;
    int startCol = column - column % 3;

    for(int i = 0; i < ROW; i++) {
        if(solution[row][i][0] == num) return 0; // Check row
    }

    for(int i = 0; i < COLUMN; i++) {
        if(solution[i][column][0] == num) return 0; // Check column
    }

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(solution[i + startRow][j + startCol][0] == num) return 0; // Check unit
        }
    }

    // Check pencil mark
    if(solution[row][column][num])
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
 * Place a randomly shuffled array in each 'unit', on the diagonal, to avoid conflicts and improve randomness of the solution
 */
void seed_random_units() {
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
                        solution[i + u][j + v][0] = num; // Seed the number
                        solution[i + u][j + v][num] = 1; // Mark the seeded number as tried
                    }
                }
            }
        }
    }
}

/**
 * Transverse through the board, trying for valid values for each cell, until a valid solution is found
 * @param row Current row
 * @param column Current column
 * @return 1 for solved board; 0 for incomplete/invalid board
 */
int backtracking(int row, int column) {
    if (row == 9) return 1; // Puzzle solved

    if (column == 9) return backtracking(row + 1, 0);

    if (solution[row][column][0] != 0) return backtracking(row, column + 1);

    for (int i = 1; i <= 9; i++) {
        if (solution[row][column][i] != 1 && validity_check(row, column, i)) {
            solution[row][column][0] = i; // Add value to board
            if (backtracking(row, column + 1)) return 1; // Puzzle solved
            solution[row][column][0] = 0; // Reset value on the board
        }
    }
    return 0; // No valid number found for this cell, backtrack
}


//duplicate board
void duplicate_board(char type, int board[ROW][COLUMN][PENCILMARKS])
{
    if(type == 'o') {
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COLUMN; j++) {
                solution_numbers_removed[i][j][0] = solution[i][j][0];
            }
        }
    }
    else
    {
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COLUMN; j++) {
                solution_playable[i][j][0] = solution_numbers_removed[i][j][0];
            }
        }
    }
}

/**
 * Function to generate random coordinates based on difficulty, time complexity O(n)
 * @param num_to_remove Numbers to be removed from the grid, depends on difficulty level
 */
void remove_numbers(int num_to_remove)
{
    // Declare and initialise array with nums 1-81
    int nums_to_remove[ROW*COLUMN];
    for(int i = 0; i < ROW*COLUMN; i++)
    {
        nums_to_remove[i] = i + 1;
    }

    shuffle(nums_to_remove, ROW*COLUMN); // Shuffle array

    for (int j = 0; j < num_to_remove; j++) // Loop through the amount of nums based on difficulty
    {
        int x = (nums_to_remove[j] - 1) / ROW; // Calculate x coordinate
        int y = (nums_to_remove[j] - 1) % COLUMN; // Calculate y coordinate
        solution_numbers_removed[x][y][0] = 0; // Set to 0 on the board
    }
    printf("Removing numbers...\n");
    sleep(1);
}
