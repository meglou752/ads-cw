
#include <pthread/pthread.h>
#include "sudoku.h"
#define EASY 1
#define MEDIUM 2
#define HARD 3
extern int player_move_counter;

int difficulty();
void display_game(int board[ROW][COLUMN][PENCILMARKS]);
void display_game_hard_difficulty(int board[ROW][COLUMN][PENCILMARKS], int bot_board[ROW][COLUMN][PENCILMARKS]);
void new_game(int difficulty_level);
void restart_game();
void interface();
void clear_input_buffer();
void home();
void progress();
void handle_input(int board[ROW][COLUMN][PENCILMARKS], int difficulty_level);
int game_complete(int board[ROW][COLUMN][PENCILMARKS]);
void* bot_thread(void* arg);
