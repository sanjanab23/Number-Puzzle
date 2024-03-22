#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 4
#define MAX_MOVES 50

// Function to clear the screen
void clearScreen() {
    system("clear"); // For Unix/Linux
    //system("cls"); // For Windows
}

// Function to display game instructions
void displayInstructions() {
    printf("Welcome to the Number Puzzle Game!\n");
    printf("Instructions:\n");
    printf("- Use arrow keys to move the cursor.\n");
    printf("- Press 'Enter' to select a number to swap with the empty space.\n");
    printf("- Arrange the numbers in ascending order.\n\n");
}

// Function to initialize the puzzle with either random or solvable numbers
void initializePuzzle(int puzzle[SIZE][SIZE], int randomize) {
    int i, j;
    srand(time(NULL));
    if (randomize) {
        for (i = 0; i < SIZE; i++) {
            for (j = 0; j < SIZE; j++) {
                puzzle[i][j] = rand() % (SIZE * SIZE); // Generate random numbers
            }
        }
    } else {
        int count = 1;
        for (i = 0; i < SIZE; i++) {
            for (j = 0; j < SIZE; j++) {
                puzzle[i][j] = count % (SIZE * SIZE); // Generate solvable numbers
                count++;
            }
        }
        // Shuffle the numbers
        for (i = SIZE - 1; i > 0; i--) {
            for (j = SIZE - 1; j > 0; j--) {
                int x = rand() % (i + 1);
                int y = rand() % (j + 1);
                int temp = puzzle[i][j];
                puzzle[i][j] = puzzle[x][y];
                puzzle[x][y] = temp;
            }
        }
    }
}

// Function to display the current state of the puzzle
void displayPuzzle(int puzzle[SIZE][SIZE], int cursorX, int cursorY) {
    int i, j;
    printf("Current Puzzle:\n");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (i == cursorX && j == cursorY) {
                printf("[ ] ");
            } else {
                printf("%3d ", puzzle[i][j]);
            }
        }
        printf("\n");
    }
}

// Function to check if the puzzle is solved
int isPuzzleSolved(int puzzle[SIZE][SIZE]) {
    int i, j, count = 1;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (puzzle[i][j] != count && !(i == SIZE - 1 && j == SIZE - 1)) {
                return 0; // Puzzle is not solved
            }
            count++;
        }
    }
    return 1; // Puzzle is solved
}

int main() {
    int puzzle[SIZE][SIZE];
    int moves = 0;
    int randomize;
    int cursorX = 0, cursorY = 0;
    
    displayInstructions();
    
    printf("Choose puzzle type (0 for solvable, 1 for random): ");
    scanf("%d", &randomize);
    
    initializePuzzle(puzzle, randomize);
    
    while (!isPuzzleSolved(puzzle) && moves < MAX_MOVES) {
        clearScreen();
        displayPuzzle(puzzle, cursorX, cursorY);
        printf("\nUse arrow keys to move the cursor. Press 'Enter' to swap.\n");
        
        // Move cursor based on user input
        char input;
        scanf(" %c", &input);
        if (input == 'w' && cursorX > 0) {
            cursorX--;
        } else if (input == 's' && cursorX < SIZE - 1) {
            cursorX++;
        } else if (input == 'a' && cursorY > 0) {
            cursorY--;
        } else if (input == 'd' && cursorY < SIZE - 1) {
            cursorY++;
        } else if (input == '\n') {
            // Swap the numbers
            int temp = puzzle[cursorX][cursorY];
            puzzle[cursorX][cursorY] = puzzle[cursorX][cursorY+1];
            puzzle[cursorX][cursorY+1] = temp;
            moves++;
        } else {
            printf("Invalid input. Use arrow keys to move the cursor.\n");
        }
    }
    
    clearScreen();
    
    if (isPuzzleSolved(puzzle)) {
        printf("Congratulations! Puzzle solved in %d moves.\n", moves);
    } else {
        printf("Sorry, you exceeded the maximum number of moves.\n");
    }
    
    return 0;
}
