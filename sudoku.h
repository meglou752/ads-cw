#ifndef ADS_SUDOKU_H
#define ADS_SUDOKU_H

#include <stdbool.h>

#define COLUMN 9
#define ROW 9
#define PENCILMARKS 9
#define UNIT_ROW 3
#define UNIT_COL 9


int display(int board[][COLUMN]); // Function declaration
int validity_check(int board[ROW][COLUMN][PENCILMARKS], int row, int column, int num);
void shuffle(int unit[]);
void seed_random_units();
int backtracking(int row, int column);
void display_board();
void display_pencilmarks();
#endif // ADS_SUDOKU_H
