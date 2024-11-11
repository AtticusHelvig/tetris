#include <cstdlib>
#include <raylib.h>
#include "board.hpp"
#include "raylib_display.hpp"
#include "piece.hpp"
#include "standard_pieces.hpp"
#include "game.hpp"

// Tick rate
const float TICKS_PER_SECOND = 30.0f;
const float TICK_TIME = 1.0f / TICKS_PER_SECOND;
int ticksElapsed = 0;

// Board size
const int NUM_ROWS = 20;
const int NUM_COLUMNS = 10;

// The piece
const int NUM_PIECES = 7;
Piece* piece;
int pieceX, pieceY;

// Game state
bool gameOver = false;

// Board
Board board(NUM_COLUMNS, NUM_ROWS);

// Display
Display *display;

namespace game {
    void init();
    void tick();
    void tickPiece();
    void drawFrame();
    bool checkCollision();
    bool attemptDrop();
    void solidifyPiece();
    void randomizePiece();
    void checkBoard();
    void clearLine(int line);
}

void game::run() {
    game::init();
    while (!gameOver) {
        tick();
        drawFrame();
    }
}

void game::drawFrame() {
    display->unlock();
    display->drawBoard();
    if (piece != nullptr) {
        display->drawPiece(piece, pieceX, pieceY);
    }
    display->lock();
}

// Will probably be used for score etc.
void game::init() {
    display = new RaylibDisplay(&board);
}

void game::tick() {
    if (IsKeyPressed(KEY_Q) || IsKeyPressed(KEY_ESCAPE)) {
        gameOver = true;
    }
    tickPiece();
    ticksElapsed++; // Times stops for no one...
}

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

bool game::checkCollision() {
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
bool game::attemptDrop() {
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

void game::solidifyPiece() {
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

void game::checkBoard() {
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

void game::clearLine(int line) {
    for (int y = line; y > 0; y--) {
        for (int x = 0; x < NUM_COLUMNS; x++) {
            board.put(x, y, board.tileAt(x, y - 1));
        }
    }
    for (int x = 0; x < NUM_COLUMNS; x++) {
        board.put(x, 0, new Tile());
    }
}

void game::randomizePiece() {
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
    pieceY = 0;
}

