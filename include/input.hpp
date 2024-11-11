#pragma once

class InputHandler {
public:
    virtual bool quit() = 0;
    virtual bool moveLeft() = 0;
    virtual bool moveRight() = 0;
    virtual bool rotateClockwise() = 0;
    virtual bool rotateCounterclockwise() = 0;
    virtual bool softDrop() = 0;
    virtual bool hardDrop() = 0;
};
