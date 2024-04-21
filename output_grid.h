#include "sudoku.h"
#define MAX_SIZE 100
//void remove_numbers(int num_to_remove);
typedef struct {
    int x;
    int y;
    int number;
} Move;

void generate_unique_solution(const int num_to_remove);
int check_uniqueness();
void undo(int board[ROW][COLUMN][PENCILMARKS]);
void redo(int board[ROW][COLUMN][PENCILMARKS]);
void push(int *top, Move stack[], Move move);
void pop(int *top, Move stack[]);
void place_move(int board[ROW][COLUMN][PENCILMARKS], int x,int y, int number);
void bot_level();
void reveal_hint(int board[ROW][COLUMN][PENCILMARKS],int x, int y);
void delete_move(int board[ROW][COLUMN][PENCILMARKS], int x, int y);
void clear_redo_stack(int *top, Move stack[]);
