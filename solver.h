
#include "sudoku.h"

extern int solution[ROW][COLUMN][PENCILMARKS];
extern int solution_numbers_removed[ROW][COLUMN][PENCILMARKS];
extern int solution_playable[ROW][COLUMN][PENCILMARKS];

void initialise_board();
int validity_check(int row, int column, int num);
void shuffle(int unit[], int size);
void seed_random_units();
int backtracking(int row, int column);
void display_board();
void duplicate_board(char type, int board[ROW][COLUMN][PENCILMARKS]);
void initialise_board(int num_to_remove);
void remove_numbers(int num_to_remove)
