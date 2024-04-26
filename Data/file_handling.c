#include "../Include/file_handling.h"

// Declare global variables
FILE *file;
char file_name[1024];
char files_dir[1024];
char file_path[2048];
char current_dir[1024];

/**
 * Save the current state of a 3D array to an output file by board
 * @param board Board to be saved
 * @param file File to be written to
 * @param board_name Board name for string compares when reading
 */
void save_3d_array(int board[ROW][COLUMN][PENCILMARKS], FILE *file, const char *board_name)
{
    // Saving array contents
    fprintf(file, "%s:\n", board_name);
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            fprintf(file, "%d ", board[i][j][0]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\n");
}


/**
 * Save the current state of a stack to an output file
 * @param stack The stack to be saved
 * @param top Pointer to the top of the stack
 * @param file File to be written to
 * @param stack_name Name of stack to be saved
 */
void save_stack(Move stack[MAX_SIZE], int top, FILE *file, const char *stack_name)
{
    fprintf(file, "%s:\n", stack_name);
    for (int i = 0; i <= top; i++) {
        fprintf(file, "%d %d %d\n", stack[i].x, stack[i].y, stack[i].number);
    }
    fprintf(file, "\n");
}


/**
 * Save game user interaction handling
 */
void save_game() {
    if (getcwd(current_dir, sizeof(current_dir)) == NULL) {
        perror("getcwd");
        return;
    }
    do {
        printf("Enter file name to save: ");
        scanf("%s", file_name);

        // Check if the file already exists
        snprintf(files_dir, sizeof(files_dir), "%s/%s/%s", current_dir, "player_saves", file_name);
        if (access(files_dir, F_OK) == 0) {
            printf("File '%s' already exists. Please choose a different name.\n", file_name);
        }
    } while (access(files_dir, F_OK) == 0);

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
    snprintf(file_path, sizeof(file_path), "%s/%s", files_dir, file_name);
    file = fopen(file_path, "w");
    if (file == NULL ) {
        perror("Error opening file for writing");
        return;
    }
    // Save difficulty for replay feature
    fprintf(file, "DIFFICULTY:\n%d\n", difficulty_level);

    // Saving 3D arrays
    save_3d_array(solution, file, "SOLUTION");
    save_3d_array(solution_numbers_removed, file, "SOLUTION_NUMS_REMOVED");
    save_3d_array(solution_playable, file, "SOLUTION_PLAYABLE");
    if(difficulty_level == HARD)
    {
        save_3d_array(bot_solution, file, "BOT_SOLUTION");
        save_3d_array(bot_solution_nums_removed,file,"BOT_SOLUTION_NUMS_REMOVED");
    }
    save_stack(undo_stack, undo_top, file, "UNDO_STACK");
    save_stack(redo_stack, redo_top, file, "REDO_STACK");
    save_stack(move_history, move_history_top, file, "MOVE_HISTORY_STACK");
    fclose(file);
    printf("Game saved successfully!\n\n\n");
    exit(0);
}

/**
 * Load a game from a specific filename in player_saves directory into play
 */
void load_game()
{
    printf("Game loaded successfully!\n");
    snprintf(file_path, sizeof(file_path), "%s/%s", files_dir, file_name); // Construct file path
    load_data(file_path); // Pass file path to load_data
    display_based_on_difficulty();
    if(difficulty_level == HARD)
    {
        while(!game_complete(solution_playable) && !game_complete(bot_solution_nums_removed))
        {
            handle_input(solution_playable);
        }
        // Bug here: bot thread will not rejoin on replay, even with re-creation of thread
        pthread_join(bot, NULL);
    }
    else
    {
        while(!game_complete(solution_playable))
        {
            handle_input(solution_playable);
        }
    }
}


/**
 * Function to delete files by name from player_saves directory
 * @param filename
 */
void delete_saves(const char *filename)
{
    load_filepath(filename);
    // Delete the file
    if (remove(files_dir) != 0) {
        perror("Error deleting file");
        return;
    }

    printf("\nGame '%s' deleted successfully!\n\n\n", filename);
    home();
}

/**
 * Helper function to load the contents of a 3D array for replay
 * @param board Board to be loaded
 * @param file File to be read from
 */
void read_3d_array(int board[ROW][COLUMN][PENCILMARKS], FILE *file)
{
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
                fscanf(file, "%d", &board[i][j][0]);
        }
    }
}


/**
 * Process stack struct objects and store them
 * @param top Pointer to the top of the stack
 * @param file File to be written to
 */
void read_stack(Move stack[MAX_SIZE], int *top, FILE *file)
{
    char line[1024];
    int x, y, number;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d %d %d", &x, &y, &number) == 3) {
            stack[++(*top)].x = x;
            stack[*top].y = y;
            stack[*top].number = number;
        }
    }
}

/**
 * Load filepath into global variable based on filename; fixed bug of not finding filepath when restarting a game on run
 * without playing a new one first.
 * @param filename Filename to be loaded
 */
void load_filepath(const char *filename)
{
    // Clear previous values; bug fix (when game has been played and saved, keeps appending filepath)
    //memset(files_dir, 0, sizeof(files_dir));
    //memset(file_path, 0, sizeof(file_path));
    //memset(current_dir, 0, sizeof(current_dir));
    if (getcwd(current_dir, sizeof(current_dir)) == NULL) {
        perror("getcwd");
        return;
    }
    // Construct the path to the file
    snprintf(files_dir, sizeof(files_dir), "%s/%s%s", current_dir, "player_saves", filename);

    printf("%s/%s%s", current_dir, "player_saves", filename);
    // Check if the file exists
    if (access(files_dir, F_OK) != 0) {
        printf("File '%s' does not exist.\n", filename);
        return;
    }
}

/**
 * Load data from the specified file back into global variables in output_grid for replay
 * @param filepath File storing contents to be loaded
 */
void load_data(const char *filepath) {
    // Load filepath
    load_filepath(filepath);
    FILE *file = fopen(files_dir, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    char line[1024];
    char key[1024];

    // Process data based on string headers using helper functions, or line comparison for single line values
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%s", key) == 1) {
            if (strcmp(key, "DIFFICULTY:") == 0) {
                fgets(line, sizeof(line), file);
                sscanf(line, "%d", &difficulty_level);
            } else if (strcmp(key, "SOLUTION:") == 0) {
                read_3d_array(solution, file);
            } else if (strcmp(key, "SOLUTION_NUMS_REMOVED:") == 0) {
                read_3d_array(solution_numbers_removed, file);
            } else if (strcmp(key, "SOLUTION_PLAYABLE:") == 0) {
                read_3d_array(solution_playable, file);
            } else if (strcmp(key, "BOT_SOLUTION:") == 0 && replay_flag != 1) {
                read_3d_array(bot_solution, file);
            } else if (strcmp(key, "BOT_SOLUTION_NUMS_REMOVED:") == 0 && replay_flag != 1) {
                read_3d_array(bot_solution_nums_removed, file);
            } else if (strcmp(key, "UNDO_STACK:") == 0 && replay_flag != 1) {
                read_stack(undo_stack, &undo_top, file);
            } else if (strcmp(key, "REDO_STACK:") == 0 && replay_flag != 1)  {
                read_stack(redo_stack, &redo_top, file);
            } else if (strcmp(key, "MOVE_HISTORY_STACK:") == 0) {
                read_stack(move_history, &move_history_top, file);
            }
        }
    }
    fclose(file);
}

/**
 * Add all of the moves from gameplay to the redo stack for looking through move history
 */
void reverse_stack()
{
    // Iterate through the move history stack in reverse order
    for (int i = move_history_top; i >= 0; i--)
    {
        // Pop each element from the move history stack
        Move topMove = move_history[i];
        push(&redo_top, &redo_stack, topMove, &redo_size);
    }
}



void cycle_through_moves()
{
    printf("Game loaded successfully!\n");
    snprintf(file_path, sizeof(file_path), "%s/%s", files_dir, file_name); // Construct file path
    load_data(file_path); // Pass file path to load_data
    reverse_stack(move_history, &move_history_top, redo_stack, &redo_top);
    display_game_replay(solution_numbers_removed);
    //handle_input_replay(solution_playable);
    while(replay_flag)
    {
        handle_input_replay(solution_numbers_removed);
    }
}
