#pragma once

#include "display.hpp"

class RaylibDisplay : public Display {
private:
    // Window
    const int WIDTH = 1000;
    const int HEIGHT = 800;
    const int FPS = 60;
    const char* TITLE = "Tetris Clone - Atticus Helvig";

    // Size of the tiles in pixels
    int tileSize;

    // Board offsets for centering
    int boardOffsetX;
    int boardOffsetY;

    // Board sizes in pixels
    int displayBoardWidth;
    int displayBoardHeight;

public:
    RaylibDisplay(Board* board);
    ~RaylibDisplay(void);
    void unlock(void) override;
    void lock(void) override;
    void drawBoard(void) override;
    void drawPiece(Piece* piece, int posX, int posY) override;
    void drawScore(unsigned int scored) override;
};
