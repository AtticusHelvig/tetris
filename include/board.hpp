#pragma once

#include <memory>
#include <raylib.h>
#include <vector>

using std::shared_ptr, std::vector;

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
    int width, height;
    vector<shared_ptr<Tile>> tiles;

public:
    Board(int width, int height);
    shared_ptr<Tile> tileAt(int x, int y);
    void put(int x, int y, shared_ptr<Tile> tile);
};

