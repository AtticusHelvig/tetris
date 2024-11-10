#pragma once

#include "board.hpp"
#include "piece.hpp"

/*
 * The Display class is intentionally lean because
 * I intend to port this game to a device without
 * access to a 'screen'. It won't use raylib but
 * I want the functionality to be basically equivalent.
*/

class Display {
protected:
    const int BOARD_WIDTH;
    const int BOARD_HEIGHT;
    Board* const board;
    bool locked;

public:
    Display(Board* board) :
        board(board),
        BOARD_WIDTH(board->getWidth()),
        BOARD_HEIGHT(board->getHeight()),
        locked(true) {};
    virtual void unlock(void) = 0;
    virtual void lock(void) = 0;
    virtual void drawBoard(void) = 0;
    virtual void drawPiece(Piece* piece, int posX, int posY) = 0;
    virtual void drawScore(unsigned int score) = 0;
};

