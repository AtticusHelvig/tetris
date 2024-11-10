#pragma once

#include <raylib.h>

class Tile {
private:
    bool filled;
    Color color;

public:
    Tile() : filled(false) {};
    Tile(Color color) : filled(true), color(color) {};
    inline bool isFilled() { return filled; }
    inline Color getColor() {
        if (filled) {
            return color;
        }
        return BLANK;
    }
};

class Board {
private:
    const int width;
    const int height;
    Tile** tiles;

public:
    Board(int width, int height);
    ~Board();
    Tile* tileAt(int x, int y);
    void put(int x, int y, Tile* tile);
    inline int getWidth(void) {
        return width;
    }
    inline int getHeight(void) {
        return height;
    }
};

