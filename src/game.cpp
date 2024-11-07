#include <iostream>
#include <memory>
#include <raylib.h>
#include "board.hpp"
#include "piece.hpp"
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

// Piece shapes
const char* T_PIECE[] = {"   ", "###", " # "};

// The piece
unique_ptr<Piece> piece = nullptr;
int pieceX, pieceY;

using namespace game;

Board board(NUM_COLUMNS, NUM_ROWS);

void game::run() {
    init();

    while (!WindowShouldClose()) {
        tick();

        BeginDrawing();
        ClearBackground(BLACK);
        drawBoard();
        drawPiece();
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

void game::tickPiece() {
    if (piece == nullptr) {
        piece = make_unique<Piece>(3, T_PIECE, MAGENTA);
        pieceX = NUM_COLUMNS / 2;
        pieceY = -1;
    }
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_X)) {
        piece->rotate();
    } else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_Z)) {
        piece->reverseRotate();
    } else if (IsKeyPressed(KEY_LEFT)) {
        pieceX--;
    } else if (IsKeyPressed(KEY_RIGHT)) {
        pieceX++;
    }

    if (ticksElapsed % 30 == 0) {
        pieceY++;
        if (pieceY > NUM_ROWS) {
            piece = nullptr;
        }
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
    const int pieceOffsetY = (piece->getWidth() - 1) * -TILE_SIZE;

    for (int x = 0; x < piece->getWidth(); x++) {
        for (int y = 0; y < piece->getWidth(); y++) {
            DrawRectangle((pieceX + x) * TILE_SIZE + BOARD_OFFSET, (pieceY + y) * TILE_SIZE + pieceOffsetY, TILE_SIZE, TILE_SIZE, piece->tileAt(x, y)->getColor());
        }
    }
}
