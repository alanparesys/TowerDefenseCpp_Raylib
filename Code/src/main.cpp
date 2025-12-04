#include <raylib.h>
#include "game.h"

int main() {
    InitWindow(1920, 1200, "Tower Defense Simple");
    SetTargetFPS(60);

    HideCursor();

    GameInit();

    GameAssets assets;
    LoadGameAssets(assets);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_F)) ToggleFullscreen();

        GameUpdate(assets);

        BeginDrawing();
        ClearBackground(DARKGRAY);
        
        CustomMouse(assets);

        EndDrawing();
    }

    UnloadGameAssets(assets);
    CloseWindow();
    return 0;
}