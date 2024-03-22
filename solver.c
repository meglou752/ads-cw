#include <stdio.h>
#include <stdbool.h>
#include "sudoku.h"

//can use the same validity checker for solution and player guess
bool validity_check(int board[ROW][COLUMN], int row, int column, int num)
{
    int start_row = row - row%3;
    int start_col = column - column%3;
    //check for num in row
    for(int i = 0; i < ROW; i++){
        if(board[row][i] == num){
            return false;
        }
    }
    //check for num in column
    for(int i = 0; i < COLUMN; i++){
        if(board[i][column] == num){
            return false;
        }
    }
    //check for num in unit
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i+start_row][j+start_col] == num){
                return false;
            }
        }
    }
    return true;
}

int sudokuHelper(int puzzle[][9], int row, int column) {
    /*
     * Iterate through the possible numbers for this empty cell
     * and recurse for every valid one, to test if it's part
     * of the valid solution.
     */
    for (int nextNum=1; nextNum < 10; nextNum++) {
        if (validity_check(puzzle, row, column, nextNum)) {
            puzzle[row][column] = nextNum;
            int nextRow, nextColumn;
            if (column == 8) {
                nextRow = row + 1;
                nextColumn = 0;
            } else {
                nextRow = row;
                nextColumn = column + 1;
            }
            if (nextRow == 9) {
                return 1; // Base case: Reached end of the puzzle
            }
            // Recurse to the next cell
            if (sudokuHelper(puzzle, nextRow, nextColumn)) {
                return 1; // If a solution is found, return immediately
            }
            // If no solution found, backtrack
            puzzle[row][column] = 0; // Reset current cell
        }
    }
    return 0; // No valid solution found
}
