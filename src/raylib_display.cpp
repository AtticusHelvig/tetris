#include <cassert>
#include <iostream>
#include <raylib.h>
#include "raylib_display.hpp"

RaylibDisplay::RaylibDisplay(Board* const board) :
    Display(board),
    tileSprite(LoadImage("../assets/tile.png"))
{
    int maxTileWidth = WIDTH / BOARD_WIDTH;
    int maxTileHeight = HEIGHT / BOARD_HEIGHT;

    if (maxTileWidth < maxTileHeight) {
        tileSize = maxTileWidth;
        boardOffsetX = 0;
        boardOffsetY = (HEIGHT - (tileSize * BOARD_HEIGHT)) / 2;
    } else {
        tileSize = maxTileHeight;
        boardOffsetX = (WIDTH - (tileSize * BOARD_WIDTH)) / 2;
        boardOffsetY = 0;
    }
    displayBoardWidth = BOARD_WIDTH * tileSize;
    displayBoardHeight = BOARD_HEIGHT * tileSize;

    InitWindow(WIDTH, HEIGHT, TITLE);
    SetTargetFPS(FPS);

    // Scale tile sprite
    ImageResize(&tileSprite, tileSize, tileSize);
    // Tricky bug, must be done **after** InitWindow
    texture = LoadTextureFromImage(tileSprite);

}

RaylibDisplay::~RaylibDisplay() {
    CloseWindow();
}

void RaylibDisplay::unlock() {
    BeginDrawing();
    ClearBackground(BLACK);
    locked = false;
}

void RaylibDisplay::lock() {
    EndDrawing();
    locked = true;
}

void RaylibDisplay::drawBoard() {
    assert(!locked);

    // Board background
    DrawRectangle(boardOffsetX, boardOffsetY, displayBoardWidth, displayBoardHeight, GRAY);

    // Draw tiles
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            // Skip unfilled tiles
            if (board->tileAt(x, y) == nullptr || !board->tileAt(x, y)->isFilled()) {
                continue;
            }
            Color tileColor = board->tileAt(x, y)->getColor();
            int tileX = x * tileSize + boardOffsetX;
            int tileY = y * tileSize + boardOffsetY;
            drawTile(board->tileAt(x, y), tileX, tileY);
        }
    }
}

// posX & poxY are coordinates on the board, not on the screen
void RaylibDisplay::drawPiece(Piece* piece, int posX, int posY) {
    assert(!locked);

    const int width = piece->getWidth();

    for (int y = 0; y < width; y++) {
        for (int x = 0; x < width; x++) {
            // Skip empty parts of the piece
            if (!piece->isColliding(x, y)) {
                continue;
            }
            Color tileColor = piece->tileAt(x, y)->getColor();
            int tileX = (x + posX) * tileSize + boardOffsetX;
            int tileY = (y + posY) * tileSize + boardOffsetY;
            drawTile(piece->tileAt(x, y), tileX, tileY);
        }
    }
}

// Temporary for testing score functionality
void RaylibDisplay::drawScore(unsigned int score) {
    std::cout << "Score: " << score << '\n';
}

// Positions are in pixels
void RaylibDisplay::drawTile(Tile* tile, int posX, int posY) {
    DrawTexture(texture, posX, posY, tile->getColor());
}
