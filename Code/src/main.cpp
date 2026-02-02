#include <raylib.h>
#include "game.h"

int main()
{
    InitWindow(1920, 1200, "Tower Defense");
    SetTargetFPS(60);
	HideCursor();
    InitAudioDevice();

    Game game;
    game.Init();

    while (!WindowShouldClose())
    {
        game.Update(GetFrameTime());
        game.Draw();
    }

    game.SaveGame();

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
