#include "sudoku.h"
int solution[ROW][COLUMN][PENCILMARKS] = {{{0}}};
int solution_playable[ROW][COLUMN][PENCILMARKS] = {{{0}}};
int solution_numbers_removed[ROW][COLUMN][PENCILMARKS] = {{{0}}};
int test_grid_forward[ROW][COLUMN][PENCILMARKS] = {{{0}}};
int test_grid_backward[ROW][COLUMN][PENCILMARKS] = {{{0}}};

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

void undo()
{
    printf("Undo\n");
}
void redo()
{
    printf("Redo\n");
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
        //printf("Placed move at %d,%d %d;\n", x, y, number);
        display_game(board);
    }
}

void reveal_hint(int board[ROW][COLUMN][PENCILMARKS],int x, int y)
{
    if(board[y][x][0] == 0)
    {
        board[y][x][0] = solution[y][x][0];
        display_game(board);
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
    }
}

void bot_level()
{

}
