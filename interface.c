#include "sudoku.h"

/**
 * Deal with user input for selecting difficulty upon new game creation
 * @return 1 for valid choice success; 0 for invalid choice
 */
int difficulty() {
    printf("Select difficulty (E, M, H, B to return home): \n");

    char difficulty;
    bool valid = false;
    scanf(" %c", &difficulty);
    clear_input_buffer();
    difficulty = toupper((unsigned char) difficulty);

    while(!valid) {
        switch (difficulty) {
            case 'E':
                valid = true;
                printf("Easy option selected.\n");
                sleep(1);
                initialise_board(EASY);
                return 1;
            case 'M':
                valid = true;
                printf("Medium option selected.\n");
                sleep(1);
                initialise_board(MEDIUM);
                return 1;
            case 'H':
                valid = true;
                printf("Hard option selected.\n");
                sleep(1);
                initialise_board(HARD);
                return 1;
            case 'B':
                valid = true;
                home();
                return 0;
            default: // Base case, read input until valid
                printf("%c is not valid, Enter a valid difficulty: ", difficulty);
                scanf(" %c", &difficulty);
                clear_input_buffer();
                return 0;
        }
    }
}

/**
 * Basic display function
 */
void display_board()
{
    printf("Sudoku Board:\n");
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            printf("%2d ", solution_numbers_removed[i][j][0]);
        }
        printf("\n");
    }
}

/**
 * Home page interface logic
 */
void home()
{
    printf("****Sudoku Game****\n\n");
    printf("Pick an option: \n");
    printf("A to start a new game\n");
    printf("B to continue an old game\n");
    printf("C to see the rules\n");
    printf("X to exit\n");

    char input;
    bool valid = false;
    scanf(" %c", &input);
    clear_input_buffer();
    input = toupper((unsigned char) input);

    while(!valid) {
        switch (input) {
            case 'A':
                new_game();
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
void new_game()
{
    printf("New game selected\n");

    // If valid choice is received, initialise and display board
    if(difficulty()){
        display_board();
    }
}

/**
 * Logic for restart game option
 */
void restart_game()
{
    printf("Restart game selected\n");

}

/**
 * Basic page of instructions for the user
 */
void how_to_play()
{
    printf("How to play selected\n");
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

