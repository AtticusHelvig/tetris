#include <memory>
#include <stdexcept>
#include "board.hpp"
#include "piece.hpp"

using std::make_shared, std::shared_ptr;

Piece::Piece(int width, const char** shape, Color color) :
    width(width),
    tiles(vector<shared_ptr<Tile>>(width * width))
{
    for (int y = 0; y < width; y++) {
        for (int x = 0; x < width; x++) {
            // If the character is a space, make an empty tile, otherwise make a colored tile.
            shared_ptr<Tile> tile = shape[y][x] == ' ' ? (make_shared<Tile>()) : (make_shared<Tile>(color));
            tiles[y * width + x] = tile;
        }
    }
}

void Piece::rotate() {
    rotation = (rotation + 1) % 4;
}

void Piece::reverseRotate() {
    rotation = (rotation + 3) % 4;
}

void Piece::resetRotation() {
    rotation = 0;
}

shared_ptr<Tile> Piece::tileAt(int x, int y) {
    switch (rotation) {
        case 0:
            return tiles[y * width + x];
        case 1:
            return tiles[((width - 1) - x) * width + y];
        case 2:
            return tiles[(width * width - 1) - (y * width + x)];
        case 3:
            return tiles[(width - 1) + (width * x) - y];
        default:
            throw new std::runtime_error("Invalid rotation.");
    }
}

bool Piece::isColliding(int x, int y) {
    return tileAt(x, y)->isFilled();
}
