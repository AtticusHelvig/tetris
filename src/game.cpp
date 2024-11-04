#include <raylib.h>
#include "game.hpp"

void game::run() {
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 800;
    const char* TITLE = "Tetris Clone - Atticus Helvig";
    const int FPS = 60;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
    SetTargetFPS(FPS);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawFPS(0, 0);
        EndDrawing();
    }

    CloseWindow();
}
