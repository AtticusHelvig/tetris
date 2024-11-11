#include <raylib.h>
#include "raylib_input.hpp"

/*
 * Default keybindings sourced from:
 * https://strategywiki.org/wiki/Tetris/Controls
*/

bool RaylibInputHandler::quit() {
    return IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_Q);
}

bool RaylibInputHandler::moveLeft() {
    return IsKeyPressed(KEY_LEFT);
}

bool RaylibInputHandler::moveRight() {
    return IsKeyPressed(KEY_RIGHT);
}

bool RaylibInputHandler::rotateClockwise() {
    return IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_X);
}

bool RaylibInputHandler::rotateCounterclockwise() {
    return IsKeyPressed(KEY_LEFT_CONTROL) || IsKeyPressed(KEY_Z);
}

bool RaylibInputHandler::softDrop() {
    return IsKeyPressed(KEY_DOWN);
}

bool RaylibInputHandler::hardDrop() {
    return IsKeyPressed(KEY_SPACE);
}
