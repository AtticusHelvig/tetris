#include "board.hpp"
#include "piece.hpp"

Piece::Piece(int width, const char** shape, Color color) :
    width(width),
    tiles(new Tile*[width * width])
{
    for (int y = 0; y < width; y++) {
        for (int x = 0; x < width; x++) {
            // If the character is a space, make an empty tile, otherwise make a colored tile.
            Tile* tile = shape[y][x] == ' ' ? nullptr : new Tile(color);
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

Tile* Piece::tileAt(int x, int y) {
    switch (rotation) {
        case 0:
            return tiles[y * width + x];
        case 1:
            return tiles[((width - 1) - x) * width + y];
        case 2:
            return tiles[(width * width - 1) - (y * width + x)];
        case 3:
            return tiles[(width - 1) + (width * x) - y];
    }
    // This should NEVER happen.
    return nullptr;
}

bool Piece::isColliding(int x, int y) {
    return tileAt(x, y)->isFilled();
}
