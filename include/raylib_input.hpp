#pragma once

#include "input.hpp"

class RaylibInputHandler : public InputHandler {
public:
    RaylibInputHandler();
    ~RaylibInputHandler();
    bool quit() override;
    bool moveLeft() override;
    bool moveRight() override;
    bool rotateClockwise() override;
    bool rotateCounterclockwise() override;
    bool softDrop() override;
    bool hardDrop() override;
};
