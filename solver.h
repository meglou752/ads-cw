
#include "sudoku.h"

extern int solution[ROW][COLUMN][PENCILMARKS];
extern int solution_numbers_removed[ROW][COLUMN];
extern int solution_playable[ROW][COLUMN];
extern int test_grid_forward[ROW][COLUMN][PENCILMARKS];
extern int test_grid_backward[ROW][COLUMN][PENCILMARKS];
extern int bot_solution[ROW][COLUMN][PENCILMARKS];
extern int bot_solution_nums_removed[ROW][COLUMN];
extern int difficulty_level;
//void initialise_board();
int validity_check(int board[ROW][COLUMN][PENCILMARKS], int row, int column, int num);
void shuffle(int unit[], int size);
void seed_random_units(int board[ROW][COLUMN][PENCILMARKS]);
int backtracking(int board[ROW][COLUMN][PENCILMARKS], int row, int column);
int reverse_backtracking(int board[ROW][COLUMN][PENCILMARKS], int row, int column);
void duplicate_board_3d_2d(int input[ROW][COLUMN][PENCILMARKS], int output[ROW][COLUMN]);
void duplicate_board_2d_3d(int input[ROW][COLUMN], int output[ROW][COLUMN][PENCILMARKS]);

void initialise_board(int num_to_remove);
void remove_numbers(int board[ROW][COLUMN], int num_to_remove);
