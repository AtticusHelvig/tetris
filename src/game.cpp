#include <memory>
#include <raylib.h>
#include "board.hpp"
#include "piece.hpp"
#include "standard_pieces.hpp"
#include "game.hpp"

using std::make_shared;

// Window
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const char* TITLE = "Tetris Clone - Atticus Helvig";
const int FPS = 60;

// Tick rate
const float TICKS_PER_SECOND = 30.0f;
const float TICK_TIME = 1.0f / TICKS_PER_SECOND;
int ticksElapsed = 0;

// Board size
const int NUM_ROWS = 20;
const int NUM_COLUMNS = 10;
const int TILE_SIZE = SCREEN_HEIGHT / NUM_ROWS;
const int BOARD_SIZE_X = NUM_COLUMNS * TILE_SIZE;
const int BOARD_SIZE_Y = NUM_ROWS * TILE_SIZE;

// Center the board
const int BOARD_OFFSET = SCREEN_WIDTH / 2 - (TILE_SIZE * NUM_COLUMNS) / 2;

// The piece
const int NUM_PIECES = 7;
Piece* piece = nullptr;
int pieceX, pieceY;

// Game state
bool gameOver = false;

using namespace game;

Board board(NUM_COLUMNS, NUM_ROWS);

void drawGridLines();

void game::run() {
    init();

    while (!gameOver && !WindowShouldClose()) {
        tick();

        BeginDrawing();
        ClearBackground(BLACK);
        drawBoard();
        drawPiece();
        drawGridLines();
        EndDrawing();
    }
    while (!WindowShouldClose()) {
        BeginDrawing();
        EndDrawing();
    }
    CloseWindow();
}

void game::init() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
    SetTargetFPS(FPS);
}

// Should be called as often as possible (e.g. every frame)
// Responsible for changing time-based state of the game
void game::tick() {
    tickPiece();
    ticksElapsed++; // Times stops for no one...
}

bool checkCollision();
bool attemptDrop();
void solidifyPiece();
void randomizePiece();

void game::tickPiece() {
    if (piece == nullptr) {
        randomizePiece();
        pieceY = -2;
    }
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_X)) {
        piece->rotate();
        if (checkCollision()) {
            piece->reverseRotate();
        }
    } else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_Z)) {
        piece->reverseRotate();
        if (checkCollision()) {
            piece->rotate();
        }
    } else if (IsKeyPressed(KEY_LEFT)) {
        pieceX--;
        if (checkCollision()) {
            pieceX++;
        }
    } else if (IsKeyPressed(KEY_RIGHT)) {
        pieceX++;
        if (checkCollision()) {
            pieceX--;
        }
    } else if (IsKeyPressed(KEY_DOWN)) {
        if (!attemptDrop()) {
            solidifyPiece();
            return;
        }
    } else if (IsKeyPressed(KEY_SPACE)) {
        while (attemptDrop()) {}
        solidifyPiece();
        return;
    }

    if (ticksElapsed % 15 == 0) {
        if (!attemptDrop()) {
            solidifyPiece();
            return;
        }
    }
}

bool checkCollision() {
    const int width = piece->getWidth();

    for (int x = 0; x < width; x++) {
        const int TILE_X = pieceX + x;
        for (int y = 0; y < width; y++) {
            const int TILE_Y = pieceY + y;
            // Check if the piece is within the side bounds
            if ((TILE_X < 0 || TILE_X >= NUM_COLUMNS) && piece-> isColliding(x, y)) {
                return true;
            }
            // Skip collisions above board
            if (TILE_Y < 0) {
                continue;
            }
            if (TILE_Y >= NUM_ROWS && piece->isColliding(x, y)) {
                return true;
            }
            if (piece->isColliding(x, y) && board.tileAt(TILE_X, TILE_Y)->isFilled()) {
                return true;
            }
        }
    }
    return false;
}

// Returns true on success
bool attemptDrop() {
    const int width = piece->getWidth();

    pieceY++;
    for (int y = 0; y < width; y++) {
        // Skip checking above the board
        if (pieceY + y < 0) {
            continue;
        }
        for (int x = 0; x < width; x++) {
            // Skip checking outside of the board
            if (pieceX + x < 0 || pieceX + x >= NUM_COLUMNS) {
                continue;
            }
            // Check if the piece is still above the bottom of the board
            if (pieceY + y >= NUM_ROWS) {
                if (piece->isColliding(x, y)) {
                    pieceY--;
                    return false;
                }
                continue;
            }
            // Check if the piece is colliding with any other tiles
            if (board.tileAt(pieceX + x, pieceY + y)->isFilled() && piece->isColliding(x, y)) {
                pieceY--;
                return false;
            }
        }
    }
    return true;
}

void checkBoard();

void solidifyPiece() {
    int width = piece->getWidth();

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < width; y++) {
            if (!piece->isColliding(x, y)) {
                continue;
            }
            if (pieceY + y < 0) {
                gameOver = true;
                return;
            }
            board.put(pieceX + x, pieceY + y, piece->tileAt(x, y));
        }
    }
    piece = nullptr;
    checkBoard();
}

void clearLine(int line);

void checkBoard() {
    for (int y = 0; y < NUM_ROWS; y++) {
        for (int x = 0; x < NUM_COLUMNS; x++) {
            if (!board.tileAt(x, y)->isFilled()) {
                break;
            }
            if (x == NUM_COLUMNS - 1) {
                clearLine(y);
            }
        }
    }
}

void clearLine(int line) {
    for (int y = line; y > 0; y--) {
        for (int x = 0; x < NUM_COLUMNS; x++) {
            board.put(x, y, board.tileAt(x, y - 1));
        }
    }
    for (int x = 0; x < NUM_COLUMNS; x++) {
        board.put(x, 0, make_shared<Tile>());
    }
}

void randomizePiece() {
    int pieceNumber = rand() % NUM_PIECES;

    switch (pieceNumber) {
        case 0:
            piece = pieces::LINE;
            break;
        case 1:
            piece = pieces::J;
            break;
        case 2:
            piece = pieces::L;
            break;
        case 3:
            piece = pieces::SQUARE;
            break;
        case 4:
            piece = pieces::S;
            break;
        case 5:
            piece = pieces::T;
            break;
        case 6:
            piece = pieces::Z;
            break;
    }
    pieceX = (NUM_COLUMNS / 2) - (piece->getWidth() / 2);
}

void game::drawBoard() {
    // Board background
    DrawRectangle(BOARD_OFFSET, 0, BOARD_SIZE_X, BOARD_SIZE_Y, GRAY);

    // Draw tiles
    for (int y = 0; y < NUM_ROWS; y++) {
        for (int x = 0; x < NUM_COLUMNS; x++) {
            DrawRectangle(BOARD_OFFSET + x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, board.tileAt(x, y)->getColor());
        }
    }
}

void game::drawPiece() {
    if (piece == nullptr) {
        return;
    }
    for (int x = 0; x < piece->getWidth(); x++) {
        for (int y = 0; y < piece->getWidth(); y++) {
            DrawRectangle((pieceX + x) * TILE_SIZE + BOARD_OFFSET, (pieceY + y) * TILE_SIZE, TILE_SIZE, TILE_SIZE, piece->tileAt(x, y)->getColor());
        }
    }
}

void drawGridLines() {
    for (int i = 0; i <= NUM_COLUMNS; i++) {
        DrawLine(i * TILE_SIZE + BOARD_OFFSET, 0, i * TILE_SIZE + BOARD_OFFSET, BOARD_SIZE_Y, RAYWHITE);
    }
    for (int i = 0; i <= NUM_ROWS; i++) {
        DrawLine(BOARD_OFFSET, i * TILE_SIZE, BOARD_OFFSET + BOARD_SIZE_X, i * TILE_SIZE, RAYWHITE);
    }
}
