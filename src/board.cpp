#include <stdexcept>
#include "board.hpp"

using std::make_shared, std::runtime_error;

Board::Board(int width, int height) : width(width), height(height), tiles(width * height, make_shared<Tile>()) {}

shared_ptr<Tile> Board::tileAt(int x, int y) {
    if (x >= width || y >= height) {
        throw new runtime_error("Cannot access a tile out of bounds.");
    }
    return tiles[width * y + x];
}

void Board::put(int x, int y, shared_ptr<Tile> tile) {
    if (x >= width || y >= height) {
        throw new runtime_error("Cannot put a tile out of bounds.");
    }
    tiles[width * y + x] = tile;
}

