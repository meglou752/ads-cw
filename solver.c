#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 9
#define COLUMN 9
#define PENCILMARKS 11 // 1 extra for the actual value

char board[ROW][COLUMN][PENCILMARKS] = {{{'0'}}};

int validity_check(int row, int column, char num) {
    int startRow = row - row % 3;
    int startCol = column - column % 3;

    // Check row
    for(int i = 0; i < 9; i++) {
        if(board[row][i][0] == num) return 0;
    }

    // Check column
    for(int i = 0; i < 9; i++) {
        if(board[i][column][0] == num) return 0;
    }

    // Check unit
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i + startRow][j + startCol][0] == num) return 0;
        }
    }

    if (board[row][column][num - '0'] == '1') {
        return 0;
    }

    return 1; // Valid placement
}



void shuffle(char unit[]) {
    int tmp;
    for(int i = 0; i < 9; i++) {
        int random = rand() % 9;
        tmp = unit[i];
        unit[i] = unit[random];
        unit[random] = tmp;
    }
}

void seed_random_units() {
    char unit[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

    srand(time(NULL));

    int unit_index = 0;
    for (int i = 0; i < ROW; i += 3) {
        for (int j = 0; j < COLUMN; j += 3) {
            if (i == j) {
                unit_index = 0;
                shuffle(unit);
                for (int u = 0; u < 3; u++) {
                    for (int v = 0; v < 3; v++) {
                        int num = unit[unit_index++];
                        board[i + u][j + v][0] = num; // Seed the number
                        board[i + u][j + v][num - '0'] = '1'; // Mark the seeded number as tried
                    }
                }
            }
        }
    }
}

int backtracking(int row, int column) {
    if (row == 9) return 1; // Puzzle solved

    if (column == 9) return backtracking(row + 1, 0);

    if (board[row][column][0] != '0') return backtracking(row, column + 1);

    for (char i = '1'; i <= '9'; i++) {
        if (board[row][column][i - '0'] != '1' && validity_check(row, column, i)) {
            board[row][column][0] = i; // Add value to board
            if (backtracking(row, column + 1)) return 1; // Puzzle solved
            //board[row][column][i] = '0';
            board[row][column][0] = '0'; // Reset value on the board
        }
    }
    return 0; // No valid number found for this cell
}

void display_board() {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            printf("%c ", board[i][j][0]);
        }
        printf("\n");
    }
}

void initialise_board() {
    seed_random_units();
    backtracking(0, 0);
    //display_board();
}