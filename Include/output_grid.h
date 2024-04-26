#include "sudoku.h"

typedef struct {
    int x;
    int y;
    int number;
} Move;

void generate_unique_solution(const int num_to_remove);
void generate_bot_solution();
int check_uniqueness();
void undo(int board[ROW][COLUMN][PENCILMARKS]);
void redo(int board[ROW][COLUMN][PENCILMARKS]);
void push(int *top, Move** stack, Move move, int *size);
void pop(int *top, int *size);
void place_move(int board[ROW][COLUMN][PENCILMARKS], int x,int y, int number, int difficulty_level);
void reveal_hint(int board[ROW][COLUMN][PENCILMARKS],int x, int y);
void delete_move(int board[ROW][COLUMN][PENCILMARKS], int x, int y);
void clear_redo_stack(int *top, Move stack[]);
void display_based_on_difficulty();
void bot_output_random();
void replay_backward(int board[ROW][COLUMN][PENCILMARKS]);
void replay_forward(int board[ROW][COLUMN][PENCILMARKS]);
void init_stacks();
void cleanup_stacks();

extern int move_history_top,undo_top,redo_top, move_size, undo_size, redo_size;
// Define pointers for stacks
extern Move* undo_stack;
extern Move* redo_stack;
extern Move* move_history;
extern int MAX_SIZE;
extern int current_size;
