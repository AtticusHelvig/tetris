#pragma once

#include "board.hpp"

class Piece {
private:
    const int width;
    int rotation = 0;
    Tile** tiles;
    Board* board;

public:
    Piece(int width, const char** shape, Color color);
    void rotate();
    void reverseRotate();
    void resetRotation();
    Tile* tileAt(int x, int y);
    bool isColliding(int x, int y);
    inline int getWidth() {
        return width;
    }
};
