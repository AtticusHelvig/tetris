#include "board.hpp"
#include <cassert>

Board::Board(int width, int height) :
    width(width),
    height(height),
    tiles(new Tile*[width * height]) 
{
    for (int i = 0; i < width * height; i++) {
          tiles[i] = new Tile();
    }
}

Board::~Board() {
    delete[] tiles;
}

Tile* Board::tileAt(int x, int y) {
    assert(x >= 0 && y >= 0 && x < width && y < height);
    return tiles[y * width + x];
}

void Board::put(int x, int y, Tile* tile) {
    assert(x >= 0 && y >= 0 && x < width && y < height);
    tiles[y * width + x] = tile;
}

