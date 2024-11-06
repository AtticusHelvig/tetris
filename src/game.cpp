#include <raylib.h>
#include "board.hpp"
#include "game.hpp"

// Window
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const char* TITLE = "Tetris Clone - Atticus Helvig";
const int FPS = 60;

// Tick rate
const float TICKS_PER_SECOND = 20;
const float TICK_TIME = 1.0 / TICKS_PER_SECOND;

// Board size
const int NUM_ROWS = 20;
const int NUM_COLUMNS = 10;
const int TILE_SIZE = SCREEN_HEIGHT / NUM_ROWS;

// Center the board
const int BOARD_OFFSET = SCREEN_WIDTH / 2 - (TILE_SIZE * NUM_COLUMNS) / 2;

using namespace game;

Board board(NUM_COLUMNS, NUM_ROWS);

void game::run() {
    init();

    while (!WindowShouldClose()) {
        tick();

        BeginDrawing();
        ClearBackground(BLACK);
        drawBoard();
        EndDrawing();
    }
    CloseWindow();
}

void game::init() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
    SetTargetFPS(FPS);
}

// Should be called as often as possible (e.g. every frame)
// Responsible for changing time-based state of the game
// Will never tick more than once at a time (though it is possible to "lag" behind)
void game::tick() {
    static int numTicks = 0;
    static float timeSinceTick = 0;
    timeSinceTick += GetFrameTime();

    // Tick only if enough time has passed [ 1 second / TPS ]
    if (!(timeSinceTick >= TICK_TIME)) {
        return;
    }

    numTicks++;
    timeSinceTick -= TICK_TIME;
}

void game::drawBoard() {
    // Board background
    DrawRectangle(BOARD_OFFSET, 0, TILE_SIZE * NUM_COLUMNS, TILE_SIZE * NUM_ROWS, GRAY);

    // Draw blocks
    for (int y = 0; y < NUM_ROWS; y++) {
        for (int x = 0; x < NUM_COLUMNS; x++) {
            DrawRectangle(BOARD_OFFSET + x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, board.tileAt(x, y)->getColor());
            Color color = board.tileAt(x, y)->getColor();
        }
    }
}
