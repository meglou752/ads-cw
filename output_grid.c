#include "sudoku.h"
int solution[ROW][COLUMN][PENCILMARKS] = {{{0}}};
int solution_playable[ROW][COLUMN][PENCILMARKS] = {{{0}}};
int solution_numbers_removed[ROW][COLUMN][PENCILMARKS] = {{{0}}};
int test_grid_forward[ROW][COLUMN][PENCILMARKS] = {{{0}}};
int test_grid_backward[ROW][COLUMN][PENCILMARKS] = {{{0}}};
int moves_top = -1,redo_top = -1, undo_stack[MAX_SIZE];
Move moves[MAX_SIZE];
Move redo_stack[MAX_SIZE];
/**
 * Check that the solution with numbers removed only has one solution
 * @return Unsuccessful/Successful
 */
int check_uniqueness()
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COLUMN; j++)
        {
            if((test_grid_forward[i][j][0] != solution[i][j][0]) || (test_grid_backward[i][j][0] != solution[i][j][0]))
            {
                return 0;
            }
        }
    }
    duplicate_board(solution_numbers_removed,solution_playable);
    return 1;
}

/**
 * Generate a solution and playable unique board
 * @param num_to_remove Based on difficulty, amount of numbers to replace with 0 on the playable grid
 * @return
 */
void generate_unique_solution(const int num_to_remove) {
    // Generate initial solution & numbers removed grid
    seed_random_units(solution);
    backtracking(solution,0,0);
    duplicate_board(solution,solution_numbers_removed);
    remove_numbers(solution_numbers_removed, num_to_remove);
    int attempts = 0;
    while(!check_uniqueness())
    {
        // Retry removing numbers until check_uniqueness returns 1
        duplicate_board(solution,solution_numbers_removed);
        remove_numbers(solution_numbers_removed, num_to_remove);
        duplicate_board(solution_numbers_removed,test_grid_forward);
        duplicate_board(solution_numbers_removed,test_grid_backward);
        backtracking(test_grid_forward,0,0);
        reverse_backtracking(test_grid_backward,0,0);
        attempts++;
    }
    //printf("No. of iterations to generate unique solution: %d\n", attempts);
}

void place_move(int board[ROW][COLUMN][PENCILMARKS], int x,int y, int number)
{
    // Check if the cell is fixed
    if (solution_numbers_removed[y][x][0] != 0)
    {
        printf("You cannot edit this cell.\n");
    }
    // Check if the number matches complete solution
    else if (solution[y][x][0] != number)
    {
        printf("Invalid choice.\n");
    }
    // Valid, place number in board
    else
    {
        board[y][x][0] = number;
        display_game(board);

        Move move = {x, y, number};
        push(&moves_top, moves, move);

        // Clear redo stack
        clear_redo_stack(&redo_top, redo_stack);
    }
}

void reveal_hint(int board[ROW][COLUMN][PENCILMARKS],int x, int y)
{
    if(board[y][x][0] == 0)
    {
        board[y][x][0] = solution[y][x][0];
        display_game(board);
        // Add to move history stack
        Move move = {x, y, board[x][y][0]};
        push(&moves_top, moves, move);
    }
    else
    {
        printf("Cell is already filled\n");
    }
}

void delete_move(int board[ROW][COLUMN][PENCILMARKS], int x, int y)
{
    if(solution_numbers_removed[y][x][0] != 0)
    {
        printf("You cannot edit this cell.\n");
    }
    else
    {
        board[y][x][0] = 0;
        display_game(board);
        Move move = {x, y, board[x][y][0]};
        push(&moves_top, moves, move);
    }
}

void bot_level()
{

}

void push(int *top, Move stack[], Move move)
{
    if (*top == MAX_SIZE - 1)
    {
        printf("\nOverflow!!");
    }
    else
    {
        *top = *top + 1;
        // Push the move onto the stack
        stack[*top] = move;
    }
}

void pop(int *top, Move stack[])
{
    if (*top == -1)
    {
        printf("\nUnderflow!!");
    }
    else
    {
        //printf("\nPopped element: %d", stack[*top]);
        *top = *top - 1;
    }
}

void undo(int board[ROW][COLUMN][PENCILMARKS])
{
    // Check if there are any moves to undo
    if (moves_top == -1)
    {
        printf("\nNo moves to undo.\n");
        return;
    }

    // Retrieve the top move from the stack
    Move topMove = moves[moves_top];
    push(&redo_top, redo_stack, topMove);
    // Update the board with the values from the top move
    // If the move is not a deletion, set the value to 0
    if(board[topMove.y][topMove.x][0] != 0) {
        board[topMove.y][topMove.x][0] = 0; // Set the cell value to 0
        display_game(board); // Display the updated board
    }
    // If deletion, add the value back from the solution
    else
    {
        board[topMove.y][topMove.x][0] = solution[topMove.y][topMove.x][0];
        display_game(board); // Display the updated board
    }
   // push(&redo_top, redo_stack, topMove);
    // Pop the top move from the stack
    pop(&moves_top, moves);
}



void redo(int board[ROW][COLUMN][PENCILMARKS])
{
    if (redo_top == -1)
    {
        printf("\nNo moves to redo.\n");
        return;
    }
    Move topMove = redo_stack[redo_top];
    if(board[topMove.y][topMove.x][0] == 0) {
        board[topMove.y][topMove.x][0] = topMove.number; // Set the cell value to 0
        display_game(board); // Display the updated board
    }
        // If deletion, add the value back from the solution
    else
    {
        board[topMove.y][topMove.x][0] = 0;
        display_game(board); // Display the updated board
    }
    push(&moves_top, moves, topMove);
    pop(&redo_top, redo_stack);
    //display_game(board);
}

void clear_redo_stack(int *top, Move stack[]) {
    *top = -1; // Reset the top index to -1 to clear the stack
}

