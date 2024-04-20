#include "sudoku.h"

//void remove_numbers(int num_to_remove);
void generate_unique_solution(const int num_to_remove);
int check_uniqueness();
void check_complete();
void undo();
void redo();
void place_move(int board[ROW][COLUMN][PENCILMARKS], int x,int y, int number);