#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Define constants for the grid size
#define ROWS 5 // Number of rows in the game board
#define COLS 5 // Number of columns in the game board

// Game board
char grid[ROWS][COLS]; // 2D array to represent the grid


void initialiseGrid()
{
    // Fill the grid with empty spaces
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            grid[i][j] = ' '; // Empty space represents an unoccupied cell
        }
    }
}

// Function to print the game board
void printGrid()
{
    // Loop through each row
    for (int i = 0; i < ROWS; i++)
    {
        // Print each cell with a separator
        for (int j = 0; j < COLS; j++)
        {
            printf(" | %c", grid[i][j]);
        }
        printf(" |\n"); // End of the row

        // Print row separator line
        for (int k = 0; k < COLS * 4 - 1; k++)
        {
            printf("-");
        }
        printf("\n");
    }
}

// Function to check if a move is valid
bool isValidMove(int row, int col)
{
    // A valid move is within bounds and the cell is empty
    return row >= 0 && row < ROWS && col >= 0 && col < COLS && grid[row][col] == ' ';
}

// Function to place a token on the grid
void placeToken(int row, int col, char token)
{
    // If the move is valid, place the token in the specified cell
    if (isValidMove(row, col))
    {
        grid[row][col] = token;
    }
}

// Function to check a line for four consecutive tokens
bool checkLine(int startRow, int startCol, int stepRow, int stepCol, char token)
{
    int count = 0; // Counter for consecutive matching tokens

    // Loop to check each position in the line
    for (int i = 0; i < 5; i++)
    {
        // Calculate the current row and column
        int row = startRow + i * stepRow;
        int col = startCol + i * stepCol;

        // Check if within bounds and matches the token
        if (row < ROWS && col < COLS && grid[row][col] == token)
        {
            count++;
            // If four consecutive tokens are found, return true
            if (count == 4)
            {
                return true;
            }
        }
        else
        {
            // Reset the counter if there's no match
            count = 0;
        }
    }
    return false; // No winning line found
}

// Function to check if there is a winner
bool checkWinner(int row, int col, char token)
{
    // Check horizontally from the starting row
    if (checkLine(row, 0, 0, 1, token))
        return true;

    // Check vertically from the starting column
    if (checkLine(0, col, 1, 0, token))
        return true;

    return false; // No winner found
}


bool isValidPlayerName(char *playerName)
{
    // Check if each character is alphabetic
    for (int i = 0; i < strlen(playerName); i++)
    {
        if (!isalpha(playerName[i]) && playerName[i] != ' ')
        {
            return false; // Invalid if non-alphabetic character is found
        }
    }
    return true;
}

// Function to get a player's move
void getPlayerMove(char *playerName, char token, int *row, int *col)
{
    // Prompt the player for their move
    printf("%s, enter your move (row col): ", playerName);
    scanf("%d %d", row, col);
}

// Main game logic
void playGame()
{
    char player1Name[50], player2Name[50];       // Names of players
    char player1Token = 'O', player2Token = 'C'; // Tokens for players
    int currentPlayer = 1;                       // Indicates the current player (1 or 2)

    // Welcome message
    printf("Welcome to Connect 4 (5x5 Grid)\n");
    printf("Instructions: The first player to align four of their tokens vertically or horizontally wins the game!\n");

    // Get player names
    while (true) {
        printf("Enter Player 1's name: ");
        fgets(player1Name, sizeof(player1Name), stdin); // Use fgets to read the name
        player1Name[strcspn(player1Name, "\n")] = '\0';  // Remove newline character
        
        // Validate the player name
        if (!isValidPlayerName(player1Name)) {
            printf("Invalid name. Please enter a valid name with only letters.\n");
            continue;
        }

        break;
    }

    while (true) {
        printf("Enter Player 2's name: ");
        fgets(player2Name, sizeof(player2Name), stdin); // Use fgets to read the name
        player2Name[strcspn(player2Name, "\n")] = '\0';  // Remove newline character

        // Validate the player name
        if (!isValidPlayerName(player2Name)) {
            printf("Invalid name. Please enter a valid name with only letters.\n");
            continue;
        }

        break;
    }

    // Initialise the game board
    initialiseGrid();

    // Main game loop
    while (true)
    {
        // Print the current state of the grid
        printGrid();

        // Variables to store the player's move
        int row, col;

        // Handle moves for Player 1
        if (currentPlayer == 1)
        {
            getPlayerMove(player1Name, player1Token, &row, &col);
            if (isValidMove(row, col))
            {
                placeToken(row, col, player1Token); // Place token on valid move
                if (checkWinner(row, col, player1Token))
                {
                    printGrid();
                    printf("%s wins!\n", player1Name); // Announce winner
                    break;                             // Exit the game loop
                }
                currentPlayer = 2; // Switch to Player 2
            }
            else
            {
                printf("Invalid move. Try again.\n"); // Prompt to retry
            }
        }
        // Handle moves for Player 2
        else
        {
            getPlayerMove(player2Name, player2Token, &row, &col);
            if (isValidMove(row, col))
            {
                placeToken(row, col, player2Token); // Place token on valid move
                if (checkWinner(row, col, player2Token))
                {
                    printGrid();
                    printf("%s wins!\n", player2Name); // Announce winner
                    break;                             // Exit the game loop
                }
                currentPlayer = 1; // Switch to Player 1
            }
            else
            {
                printf("Invalid move. Try again.\n"); // Prompt to retry
            }
        }
    }
}

int main()
{
    playGame(); // Start the game
    return 0;
}
