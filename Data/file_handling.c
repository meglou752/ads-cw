#include "../Include/file_handling.h"
#include <stdio.h>


void save_3d_array(int board[ROW][COLUMN][PENCILMARKS], FILE *file, const char *board_name)
{
    // Saving solution array
    fprintf(file, "%s:\n", board_name);
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            fprintf(file, "%d ", board[i][j][0]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\n");
}

void save_stack(Move stack[MAX_SIZE], int top, FILE *file, const char *stack_name)
{
    fprintf(file, "%s:\n", stack_name);
    for (int i = 0; i <= top; i++) {
        fprintf(file, "%d %d %d\n", stack[i].x, stack[i].y, stack[i].number);
    }
    fprintf(file, "\n");
}

/**
* Save Game
*/
//Appending difficulty, progress?, board state, board solution, board_nums_rem
//if hard, append bot states (initial & current)
//undo + redo stack states (pop to array)
//Check game id,name already exists in sub-dir; if yes, overwrite file data, if no, create new file new


// Save Game
void save_game() {

    // Save relevant objects depending on difficulty
    FILE *file;
    char file_name[1024];
    char files_dir[1024];
    printf("Enter file name to save: ");
    scanf("%s", file_name);

    // Get the current working directory
    char current_dir[1024];
    if (getcwd(current_dir, sizeof(current_dir)) == NULL) {
        perror("getcwd");
        return;
    }

    // Construct the path to the 'player_saves' subdirectory
    snprintf(files_dir, sizeof(files_dir), "%s/%s", current_dir, "player_saves");

    // Check if the 'player_saves' directory exists, if not, create it
    struct stat st = {0};
    if (stat(files_dir, &st) == -1) {
        printf("Creating 'player_saves' directory...\n");
        if (mkdir(files_dir, 0700) == -1) {
            perror("mkdir");
            return;
        }
    }

    // Open file for writing
    char file_path[2048];
    snprintf(file_path, sizeof(file_path), "%s/%s", files_dir, file_name);
    file = fopen(file_path, "w");
    if (file == NULL ) {
        perror("Error opening file for writing");
        return;
    }

    // Saving 3D arrays
    save_3d_array(solution, file, "S");
    save_3d_array(solution_numbers_removed, file, "SNR");
    save_3d_array(solution_playable, file, "SP");
    if(difficulty_level == HARD)
    {
        save_3d_array(bot_solution, file, "BS");
        save_3d_array(bot_solution_nums_removed,file,"BSNR");
    }
    save_stack(moves, moves_top, file, "MS");
    save_stack(redo_stack, redo_top, file, "RS");

    fclose(file);
    printf("Game saved successfully!\n\n\n");
    home();
}



/**
* Load game
*/
//Depending on difficulty , loop through 'objects' in file and assign to global variables
//Rest is handled in restart game
void load_game()
{
    printf("Load game\n");
}

void check_saves()
{
    printf("Check saves\n");
}

