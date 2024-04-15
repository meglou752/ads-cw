#ifndef ADS_SUDOKU_H
#define ADS_SUDOKU_H

#include <stdbool.h>

#define COLUMN 9
#define ROW 9
#define PENCILMARKS 9

#define POSSVAL 9
#define EMPTY_CELL 0
int display(int board[][COLUMN]); // Function declaration
int validity_check(int board[ROW][COLUMN][PENCILMARKS], int row, int column, int num);
int shuffle(int unit[]);
void seed_random_units();
int backtracking(int row, int column);
void display_board();
int isValid(int number, int puzzle[][9], int row, int column);
#endif // ADS_SUDOKU_H
