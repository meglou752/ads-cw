#include "sudoku.h"
void save_game();
void load_game();
void check_saves();
//void save_3d_array(int board[ROW][COLUMN][PENCILMARKS], FILE *file, const char *board_name);
void delete_saves(const char *filename);
void load_data(const char *filepath);
//void read_3d_array(int board[ROW][COLUMN][PENCILMARKS], FILE *file);
//void read_stack(Move stack[MAX_SIZE], int *top, FILE *file);

void load_filepath(const char *filename);