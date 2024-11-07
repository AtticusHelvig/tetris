#include <memory>
#include <raylib.h>
#include "board.hpp"
#include "piece.hpp"
#include "standard_pieces.hpp"
#include "game.hpp"

using std::unique_ptr, std::make_unique;

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

void game::run() {
    init();

    while (!gameOver && !WindowShouldClose()) {
        tick();

        BeginDrawing();
        ClearBackground(BLACK);
        drawBoard();
        drawPiece();
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
    } else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_Z)) {
        piece->reverseRotate();
    } else if (IsKeyPressed(KEY_LEFT)) {
        pieceX--;
    } else if (IsKeyPressed(KEY_RIGHT)) {
        pieceX++;
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

    if (ticksElapsed % 30 == 0) {
        if (!attemptDrop()) {
            solidifyPiece();
            return;
        }
    }
}

// Returns true on success
bool attemptDrop() {
    int width = piece->getWidth();

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
}

void randomizePiece() {
    int pieceNumber = rand() % NUM_PIECES;
    switch (pieceNumber) {
        case 0:
            piece = pieces::LINE;
            return;
        case 1:
            piece = pieces::J;
            return;
        case 2:
            piece = pieces::L;
            return;
        case 3:
            piece = pieces::SQUARE;
            return;
        case 4:
            piece = pieces::S;
            return;
        case 5:
            piece = pieces::T;
            return;
        case 6:
            piece = pieces::Z;
            return;
    }
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
