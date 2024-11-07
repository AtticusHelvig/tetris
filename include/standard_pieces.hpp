#pragma once

#include "piece.hpp"

namespace pieces {
    const char* LINE_PATTERN[] = {"    ", "####", "    ", "    "};
    Piece* const LINE = new Piece(4, LINE_PATTERN, SKYBLUE);
    const char* J_PATTERN[] = {"#  ", "###", "   "};
    Piece* const J = new Piece(3, J_PATTERN, BLUE);
    const char* L_PATTERN[] = {"  #", "###", "   "};
    Piece* const L = new Piece(3, L_PATTERN, ORANGE);
    const char* SQUARE_PATTERN[] = {"##", "##"};
    Piece* const SQUARE = new Piece(2, SQUARE_PATTERN, YELLOW);
    const char* S_PATTERN[] = {" ##", "## ", "   "};
    Piece* const S = new Piece(3, S_PATTERN, GREEN);
    const char* T_PATTERN[] = {" # ", "###", "   "};
    Piece* const T = new Piece(3, T_PATTERN, PURPLE);
    const char* Z_PATTERN[] = {"## ", " ##", "   "};
    Piece* const Z = new Piece(3, Z_PATTERN, RED);
}
