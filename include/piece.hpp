#pragma once

#include <memory>
#include <vector>
#include <board.hpp>

using std::shared_ptr, std::vector;

class Piece {
private:
    const int width;
    int rotation = 0;
    vector<shared_ptr<Tile>> tiles;
    shared_ptr<Board> board;

public:
    Piece(int width, const char** shape, Color color);
    void rotate();
    void reverseRotate();
    shared_ptr<Tile> tileAt(int x, int y);
    bool isColliding(int x, int y);
    inline int getWidth() {
        return width;
    }
};
