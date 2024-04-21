#include "sudoku.h"

/**
 * Deal with user input for selecting difficulty upon new game creation
 * @return 1 for valid choice success; 0 for invalid choice
 */
char difficulty_setting;
int moves_counter;
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
                return 1;
            case 'M':
                valid = true;
                new_game(MEDIUM);
                return 1;
            case 'H':
                valid = true;
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
 * Basic display function
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

    asterisk_value = 39 * progress_percentage / 100; // Calculate number of asterisks
    printf("  ");
    // Display asterisks
    for (int k = 0; k < asterisk_value; k++)
    {
        printf("*");
    }
    printf("%d%%", progress_percentage);
    printf("\n");
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
    printf("\t     C to see the rules\n");
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
            case 'C':
                how_to_play();
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
 * Logic for new game option
 */
void new_game(int difficulty_level)
{
    // If valid choice is received, initialise and display board
        generate_unique_solution(difficulty_level);
        if(difficulty_level == HARD)
        {
            display_game(solution_playable);
            bot_level();
        }
        else
        {
            display_game(solution_playable);

        }

        while(!game_complete(solution_playable))
        {
            handle_input(solution_playable);
        }
    }


void handle_input(int board[ROW][COLUMN][PENCILMARKS])
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
        case 'P': // Assuming 'P' as the command to place a move
            // Assuming the input format for placing a move is: x,y number
            printf("Enter move (format: x,y number): ");
            if (scanf("%d,%d %d", &x, &y, &number) == 3) {
                // Logic to place a move
                place_move(board, x, y, number);
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
 */
void restart_game()
{
}

/**
 * Basic page of instructions for the user
 */
void how_to_play()
{
}

/**
 * Interface logic
 */
void interface()
{
    home();
}


/**
 * Clear input character from scanf function
 */
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


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
    char save;
    printf("\nGame complete! Would you like to save the game? (Y/N)\n");
    scanf(" %c", &save);
    clear_input_buffer();
    save = toupper((unsigned char)save);
    if(save == 'Y')
    {
        save_game();
    }
    else
    {
        home();
    }
    return 1;
}