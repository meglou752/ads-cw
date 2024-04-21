
#include "sudoku.h"
#define EASY 30
#define MEDIUM 40
#define HARD 50

int difficulty();
void display_game(int board[ROW][COLUMN]);
void display_game_hard_difficulty(int board[ROW][COLUMN], int bot_board[ROW][COLUMN]);
void new_game(int difficulty_level);
void restart_game();
void how_to_play();
void interface();
void clear_input_buffer();
void home();
void progress();
void handle_input(int board[ROW][COLUMN], int difficulty_level);
int game_complete(int board[ROW][COLUMN]);
