#ifndef ADS_SUDOKU_H
#define ADS_SUDOKU_H

#include <stdbool.h>

#define COLUMN 9
#define ROW 9
#define POSSVAL 9
#define EMPTY_CELL 0

int validity_check(int board[ROW][COLUMN], int row, int column, int num);
int shuffle(int unit[]);
void seed_random_units();
int backtracking(int row, int column);
void display_board();
#endif // ADS_SUDOKU_H
