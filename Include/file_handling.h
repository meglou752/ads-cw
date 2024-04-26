#include "sudoku.h"
void save_game();
void load_game();
void delete_saves(const char *filename);
void load_data(const char *filepath);

// Commented out declarations; compiler doesn't like 'FILE' parameter here
//void save_3d_array(int board[ROW][COLUMN][PENCILMARKS], FILE *file, const char *board_name);
//void read_3d_array(int board[ROW][COLUMN][PENCILMARKS], FILE *file);
//void read_stack(Move stack[MAX_SIZE], int *top, FILE *file);

void load_filepath(const char *filename);
void cycle_through_moves();
void reverse_stack();
