
#include "sudoku.h"
#define EASY 5
#define MEDIUM 40
#define HARD 50
#define EASY_PERCENTAGE_PM 0.04
#define MEDIUM_PERCENTAGE_PM 0.033
#define HARD_PERCENTAGE_PM 0.029

int difficulty();

void display_game(int board[ROW][COLUMN][PENCILMARKS]);
void new_game(int difficulty_level);
void restart_game();
void how_to_play();
void interface();
void clear_input_buffer();
void home();
void progress();
void handle_input(int board[ROW][COLUMN][PENCILMARKS]);
int game_complete(int board[ROW][COLUMN][PENCILMARKS]);
