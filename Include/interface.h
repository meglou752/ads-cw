
#include <pthread/pthread.h>
#include "sudoku.h"
#define EASY 30
#define MEDIUM 40
#define HARD 50

#define MAX_FILE_PATH_LENGTH 1024
extern int player_move_counter;
extern char file_name[1024];

int difficulty();
void display_game(int board[ROW][COLUMN][PENCILMARKS]);
void display_game_hard_difficulty(int board[ROW][COLUMN][PENCILMARKS], int bot_board[ROW][COLUMN][PENCILMARKS]);
void new_game();
int restart_game();
void interface();
void clear_input_buffer();
void home();
void progress();
void handle_input(int board[ROW][COLUMN][PENCILMARKS]);
int game_complete(int board[ROW][COLUMN][PENCILMARKS]);
void* bot_thread();
int enter_filename(char *file_path, const char *current_dir);
extern pthread_t bot;
