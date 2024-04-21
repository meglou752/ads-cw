#include "sudoku.h"

//void remove_numbers(int num_to_remove);
void generate_unique_solution(const int num_to_remove);
int check_uniqueness();
void undo();
void redo();
void place_move(int board[ROW][COLUMN][PENCILMARKS], int x,int y, int number);
void bot_level();
void reveal_hint(int board[ROW][COLUMN][PENCILMARKS],int x, int y);
void delete_move(int board[ROW][COLUMN][PENCILMARKS], int x, int y);

