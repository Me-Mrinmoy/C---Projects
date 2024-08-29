//Creating a fully functional chess game in C with all the rules, piece movements, and checkmate detection is a complex task.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 8

char board[SIZE][SIZE];

// Function to initialize the chess board with pieces
void initBoard() {
    char initial_board[SIZE][SIZE] = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
    };

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = initial_board[i][j];
        }
    }
}

// Function to print the chess board
void printBoard() {
    printf("  a b c d e f g h\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", 8 - i);
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("%d\n", 8 - i);
    }
    printf("  a b c d e f g h\n");
}

// Function to convert chess notation (e.g., "e2") to array indices
int convertNotation(char col, char row, int* x, int* y) {
    *x = SIZE - (row - '0');
    *y = col - 'a';
    return (*x >= 0 && *x < SIZE && *y >= 0 && *y < SIZE);
}

// Function to check if a move is within the board
int isValidMove(int sx, int sy, int dx, int dy) {
    return (dx >= 0 && dx < SIZE && dy >= 0 && dy < SIZE && (sx != dx || sy != dy));
}

// Function to move a piece from (sx, sy) to (dx, dy)
int movePiece(int sx, int sy, int dx, int dy) {
    char piece = board[sx][sy];
    char target = board[dx][dy];

    // Check if the source and destination are valid
    if (piece == ' ' || !isValidMove(sx, sy, dx, dy)) {
        return 0;
    }

    // Basic movement rules for pawns
    if (tolower(piece) == 'p') {
        int direction = (piece == 'P') ? -1 : 1;
        if (sx + direction == dx && sy == dy && target == ' ') {
            // Move forward
            board[dx][dy] = piece;
            board[sx][sy] = ' ';
            return 1;
        }
        if (sx + direction == dx && abs(sy - dy) == 1 && islower(target) != islower(piece)) {
            // Capture diagonally
            board[dx][dy] = piece;
            board[sx][sy] = ' ';
            return 1;
        }
    }

    // Basic movement rules for rooks
    if (tolower(piece) == 'r') {
        if (sx == dx || sy == dy) {
            // Check path is clear
            for (int i = 1; i < SIZE; i++) {
                int nx = sx + (dx - sx == 0 ? 0 : i * ((dx - sx) / abs(dx - sx)));
                int ny = sy + (dy - sy == 0 ? 0 : i * ((dy - sy) / abs(dy - sy)));
                if (nx == dx && ny == dy) break;
                if (board[nx][ny] != ' ') return 0;
            }
            board[dx][dy] = piece;
            board[sx][sy] = ' ';
            return 1;
        }
    }

    // Add other piece movement rules (knight, bishop, queen, king)...

    return 0;
}

int main() {
    char start[3], end[3];
    int sx, sy, dx, dy;

    initBoard();
    printBoard();

    while (1) {
        printf("Enter your move (e.g., e2 e4): ");
        scanf("%s %s", start, end);

        if (!convertNotation(start[0], start[1], &sx, &sy) ||
            !convertNotation(end[0], end[1], &dx, &dy)) {
            printf("Invalid move format!\n");
            continue;
        }

        if (movePiece(sx, sy, dx, dy)) {
            printBoard();
        } else {
            printf("Invalid move!\n");
        }
    }

    return 0;
}
