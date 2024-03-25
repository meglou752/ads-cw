#ifndef ADS_SUDOKU_H
#define ADS_SUDOKU_H

#include <stdbool.h>

#define COLUMN 9
#define ROW 9
#define POSSVAL 9
#define EMPTY_CELL 0

int display(int board[][COLUMN]); // Function declaration
int validity_check(int board[ROW][COLUMN], int row, int column, int num);
bool fill(int board[ROW][COLUMN]);
int sudoku_helper(int puzzle[][9], int row, int column);
int isValid(int number, int puzzle[][9], int row, int column);
#endif // ADS_SUDOKU_H
