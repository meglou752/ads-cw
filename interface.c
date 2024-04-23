#include "sudoku.h"

/**
 * Deal with user input for selecting difficulty upon new game creation
 * @return 1 for valid choice success; 0 for invalid choice
 */
char difficulty_setting;
int difficulty_level;
int player_move_counter;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * Entry point
 */
void interface()
{
    home();
}

/**
 * Home page interface logic
 */
void home()
{
    printf("\t   ******SUDOKU GAME******\n");
    printf("\t        Pick an option: \n");
    printf("\t    A to start a new game\n");
    printf("\t   B to continue an old game\n");
    printf("\t          X to exit\n");
    printf(("INPUT: "));
    char input;
    bool valid = false;
    scanf(" %c", &input);
    clear_input_buffer();
    input = toupper((unsigned char) input);

    while(!valid) {
        switch (input) {
            case 'A':
                difficulty();
                valid = true;
                break;
            case 'B':
                restart_game();
                valid = true;
                break;
            case 'X':
                valid = true;
                break;
            default:
                printf("%c is not valid, enter a valid choice: ", input);
                scanf(" %c", &input);
                input = toupper((unsigned char) input);
                clear_input_buffer();
                break;
        }
    }
}

/**
 * Difficulty interface logic
 * @return Validity of choice
 */
int difficulty() {
    printf("\n\t\t  SELECT DIFFICULTY\n");
    printf("\t        Pick an option: \n");
    printf("\t           E (easy)\n");
    printf("\t          M (medium)\n");
    printf("\t           H (hard)\n");
    printf("\t         B to go home\n");
    printf(("INPUT: "));
    bool valid = false;
    scanf(" %c", &difficulty_setting);
    clear_input_buffer();
    difficulty_setting = toupper((unsigned char) difficulty_setting);

    while(!valid) {
        switch (difficulty_setting) {
            case 'E':
                valid = true;
                new_game(EASY);
                difficulty_level = EASY;
                return 1;
            case 'M':
                valid = true;
                new_game(MEDIUM);
                difficulty_level = MEDIUM;
                return 1;
            case 'H':
                valid = true;
                difficulty_level = HARD;
                new_game(HARD);
                return 1;
            case 'B':
                valid = true;
                home();
                return 0;
            default: // Base case, read input until valid
                printf("%c is not valid, Enter a valid difficulty: ", difficulty_setting);
                scanf(" %c", &difficulty_setting);
                clear_input_buffer();
                difficulty_setting = toupper((unsigned char) difficulty_setting);
                break;
        }
    }
}


/**
 * Basic display function for easy and medium difficulty
 */
void display_game(int board[ROW][COLUMN][PENCILMARKS])
{
    printf("\n  ◦ 0   1   2 ◦ 3   4   5 ◦ 6   7   8 ◦\n");
    printf("◦ ╔═══════════╤═══════════╤═══════════╗");
    printf("\n");

    for (int i = 0; i < ROW; i++) {
        if (i % 3 == 0 && i != 0) {
            if(i != 3) {
                printf("◦ ╟───────────│───────────│───────────╢\n"); // Print horizontal divider after every 3 rows
            }
            else
            {
                printf("◦ ╟───────────│───────────│───────────╢ To get a hint: H\n");
            }
        }

        for (int j = 0; j < COLUMN; j++) {
            if (j % 3 == 0 && j != 0) {
                printf(" │ "); // Print vertical divider after every 3 columns within a row
            }
            else if(j == 0)
            {
                printf("%d ║ ",i);
            }
            else if (j == 8)
            {
                printf("%2d ", board[i][j][0]);
                printf(" ║ ");
                if(i == 0)
                {
                    printf("To place a move: P");
                }
                else if( i == 1)
                {
                    printf("To undo:  U");
                }
                else if (i == 2)
                {
                    printf("To redo: R ");
                }
                else if (i == 3)
                {
                    printf("To delete a move: D");
                }
                else if (i == 4)
                {
                    printf("To save and exit: S ");
                }
            }
            if(j != 8) {
                printf("%2d ", board[i][j][0]);
            }
        }
        printf("\n");
    }
    printf("◦ ╚═══════════╧═══════════╧═══════════╝\n");
    progress();
}


/**
 * Calculate progress based on number of cells filled in compared to number of blank cells output originally
 */
void progress()
{
    // Initialize variables
    int initial = 0, changed = 0, progress_num, progress_percentage, asterisk_value;

    // Calculate difference
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COLUMN; j++)
        {
            if (solution_numbers_removed[i][j][0] == 0)
            {
                initial++;
            }
            if (solution_playable[i][j][0] == 0)
            {
                changed++;
            }
        }
    }
    // Calculate progress percentage
    if (initial != 0) {
        progress_num = initial - changed;
        progress_percentage = (progress_num * 100) / initial;
    } else {
        progress_percentage = 0;
    }

    asterisk_value = 39 * progress_percentage / 100; // Calculate weighting of asterisks
    printf("  ");
    // Display asterisks
    for (int k = 0; k < asterisk_value; k++)
    {
        printf("*");
    }
    printf("%d%%", progress_percentage);
    printf("\n");
}


void* bot_thread(void* arg) {
    while (!game_complete(bot_solution_nums_removed)) {
        // Sleep for a random interval between 20 and 30 seconds
        int random_time = rand() % 11 + 20;
        sleep(random_time);

        // Make a bot move
        pthread_mutex_lock(&mutex);
        bot_output_random();
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
/**
 * Logic for new game menu option
 */
void new_game(int difficulty_level)
{
        // Create seperate threads for bot
        pthread_t bot;
        pthread_create(&bot, NULL, bot_thread, NULL);

        // If valid choice is received, initialise and display game based on difficulty
        generate_unique_solution(difficulty_level);
        if(difficulty_level == HARD)
        {
            generate_bot_solution();
            display_game_hard_difficulty(solution_playable, bot_solution_nums_removed);
        }
        else
        {
            display_game(solution_playable);

        }

    if(difficulty_level == HARD)
    {
        while(!game_complete(solution_playable))
        {
            handle_input(solution_playable, difficulty_level);
        }
        // Enter bot thread
        pthread_join(bot, NULL);

    }
    else
    {
        while(!game_complete(solution_playable))
        {
            handle_input(solution_playable, difficulty_level);
        }
    }
}

/**
 * Gameplay input handling
 * @param board Playable board
 * @param difficulty_level
 */
void handle_input(int board[ROW][COLUMN][PENCILMARKS], int difficulty_level)
{
    int x, y, number;
    char input;
    printf("INPUT: ");
    scanf(" %c", &input);
    clear_input_buffer();
    input = toupper((unsigned char)input);


        switch (input) {
        case 'S':
            // Logic to save and exit
            save_game();
            break;
        case 'U':
            // Logic to undo
            undo(solution_playable);
            break;
        case 'R':
            // Logic to redo
            redo(solution_playable);
            break;
        case 'P':
            printf("Enter move (format: x,y number): ");
            if (scanf("%d,%d %d", &x, &y, &number) == 3) {
                // Logic to place a move
                place_move(board, x, y, number, difficulty_level);
                player_move_counter++;
            } else {
                printf("Invalid input\n");
                clear_input_buffer();
            }
            break;
        case 'H':
            printf("Enter cell location (format: x,y): ");
            if (scanf("%d,%d", &x,&y) == 2)
            {
                reveal_hint(board,x,y);
                player_move_counter++;
            }
            else
            {
                printf("Invalid cell location\n");
                clear_input_buffer();
            }
            break;
        case 'D':
            printf("Enter cell location (format: x,y): ");
            if (scanf("%d,%d", &x,&y) == 2)
            {
                delete_move(board,x,y);
            }
            else
            {
                printf("Invalid cell location\n");
                clear_input_buffer();
            }
            break;
    }
}

/**
 * Logic for restart game option
 * Needs implementation
 */
void restart_game()
{
    load_game();
}



/**
 * Clear input character from scanf function
 */
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


/**
 * Checks if the current state of the board is complete
 * @param board Playable board
 * @return 0 for incomplete; 1 for complete
 */
int game_complete(int board[ROW][COLUMN][PENCILMARKS])
{
    for(int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COLUMN; j++)
        {
            if (board[i][j][0] == 0)
            {
                return 0;
            }
        }
    }
    // Game complete
    if(difficulty_setting == 'H')
    {
        return 1;
    }
    else {
        char save;
        printf("\nGame complete! Would you like to save the game? (Y/N)\n");
        scanf(" %c", &save);
        clear_input_buffer();
        save = toupper((unsigned char) save);
        if (save == 'Y') {
            save_game();
        } else {
            home();
        }
        return 1;
    }
}





// BOT FUNCTIONS //

/**
 * Display both the playable board and the bot board (looking for more efficient implementation)
 * @param board Playable board
 * @param bot_board  Bot, non-playable board
 */
void display_game_hard_difficulty(int board[ROW][COLUMN][PENCILMARKS], int bot_board[ROW][COLUMN][PENCILMARKS])
{
    printf("\n  ◦ 0   1   2 ◦ 3   4   5 ◦ 6   7   8 ◦\t\t\t\t\t\t\t\t\t\t\t   BOT GRID");
    printf("\n◦ ╔═══════════╤═══════════╤═══════════╗\t\t\t\t\t\t\t\t╔═══════════╤═══════════╤═══════════╗");
    printf("\n");

    for (int i = 0; i < ROW; i++) {
        if (i % 3 == 0 && i != 0) {
            if(i != 3) {
                printf("◦ ╟───────────┼───────────┼───────────╢\t\t\t\t\t\t\t\t╟───────────┼───────────┼───────────╢\n"); // Print horizontal divider after every 3 rows
            }
            else
            {
                printf("◦ ╟───────────┼───────────┼───────────╢ To get a hint: H\t\t\t╟───────────┼───────────┼───────────╢\n");
            }
        }

        for (int j = 0; j < COLUMN; j++) {
            if (j % 3 == 0 && j != 0) {
                printf(" │ "); // Print vertical divider after every 3 columns within a row
            }
            else if(j == 0)
            {
                printf("%d ║ ",i);
            }
            else if (j == 8)
            {
                printf("%2d ", board[i][j][0]);
                printf(" ║");
                if(i == 0)
                {
                    printf("To place a move: P");
                }
                else if( i == 1)
                {
                    printf("To undo:  U");
                }
                else if (i == 2)
                {
                    printf("To redo: R ");
                }
                else if (i == 3)
                {
                    printf("To delete a move: D");
                }
                else if (i == 4)
                {
                    printf("To save and exit: S ");
                }
            }
            if(j != 8) {
                printf("%2d ", board[i][j][0]);
            }
        }


        if(i == 0) {
            // Printing the bot grid
            printf("\t\t");
            for (int j = 0; j < COLUMN; j++) {
                if (j % 3 == 0 && j != 0) {
                    printf(" │ "); // Print vertical divider after every 3 columns within a row
                } else if (j == 0) {
                    printf("    ║ ");
                } else if (j == 8) {
                    printf("%2d ", bot_board[i][j][0]);
                    printf(" ║ ");
                }
                if (j != 8) {
                    printf("%2d ", bot_board[i][j][0]);
                }
            }
        }
        else if(i == 1)
        {
            printf("\t\t\t\t");
            for (int j = 0; j < COLUMN; j++) {
                if (j % 3 == 0 && j != 0) {
                    printf(" │ "); // Print vertical divider after every 3 columns within a row
                } else if (j == 0) {
                    printf("    ║ ");
                } else if (j == 8) {
                    printf("%2d ", bot_board[i][j][0]);
                    printf(" ║ ");
                }
                if (j != 8) {
                    printf("%2d ", bot_board[i][j][0]);
                }
            }
        }
        else if (i == 2)
        {
            printf("\t\t\t\t");
            for (int j = 0; j < COLUMN; j++) {
                if (j % 3 == 0 && j != 0) {
                    printf(" │ "); // Print vertical divider after every 3 columns within a row
                } else if (j == 0) {
                    printf("    ║ ");
                } else if (j == 8) {
                    printf("%2d ", bot_board[i][j][0]);
                    printf(" ║ ");
                }
                if (j != 8) {
                    printf("%2d ", bot_board[i][j][0]);
                }
            }
        }
        else if (i == 3 || i == 4)
        {
            printf("\t\t");
            for (int j = 0; j < COLUMN; j++) {
                if (j % 3 == 0 && j != 0) {
                    printf(" │ "); // Print vertical divider after every 3 columns within a row
                } else if (j == 0) {
                    printf("    ║ ");
                } else if (j == 8) {
                    printf("%2d ", bot_board[i][j][0]);
                    printf(" ║ ");
                }
                if (j != 8) {
                    printf("%2d ", bot_board[i][j][0]);
                }
            }
        }
        else
        {
            printf("\t\t\t\t\t\t\t");
            for (int j = 0; j < COLUMN; j++) {
                if (j % 3 == 0 && j != 0) {
                    printf(" │ "); // Print vertical divider after every 3 columns within a row
                } else if (j == 0) {
                    printf("    ║ ");
                } else if (j == 8) {
                    printf("%2d ", bot_board[i][j][0]);
                    printf(" ║ ");
                }
                if (j != 8) {
                    printf("%2d ", bot_board[i][j][0]);
                }
            }
        }

        printf("\n");
    }
    printf("◦ ╚═══════════╧═══════════╧═══════════╝\t\t\t\t\t\t\t\t╚═══════════╧═══════════╧═══════════╝\n");
    progress();
}

