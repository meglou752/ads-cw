
#include "sudoku.h"

extern int solution[ROW][COLUMN][PENCILMARKS];
extern int solution_numbers_removed[ROW][COLUMN][PENCILMARKS];
extern int solution_playable[ROW][COLUMN][PENCILMARKS];
extern int test_grid_forward[ROW][COLUMN][PENCILMARKS];
extern int test_grid_backward[ROW][COLUMN][PENCILMARKS];

//void initialise_board();
int validity_check(int board[ROW][COLUMN][PENCILMARKS], int row, int column, int num);
void shuffle(int unit[], int size);
void seed_random_units(int board[ROW][COLUMN][PENCILMARKS]);
int backtracking(int board[ROW][COLUMN][PENCILMARKS], int row, int column);
int reverse_backtracking(int board[ROW][COLUMN][PENCILMARKS], int row, int column);
void duplicate_board(int input[ROW][COLUMN][PENCILMARKS], int output[ROW][COLUMN][PENCILMARKS]);
void initialise_board(int num_to_remove);
void remove_numbers(int board[ROW][COLUMN][PENCILMARKS], int num_to_remove);