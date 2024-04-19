#ifndef ADS_SUDOKU_H
#define ADS_SUDOKU_H

#include <stdbool.h>

#define COLUMN 9
#define ROW 9
#define POSSVAL 9
#define EMPTY_CELL 0

int validity_check(char board[ROW][COLUMN], int row, int column, char num);
void shuffle(char unit[]);
void seed_random_units();
int backtracking(int row, int column);
void initialise_board();
void display_board();
#endif // ADS_SUDOKU_H
