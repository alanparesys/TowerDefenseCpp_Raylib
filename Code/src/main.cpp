#include <raylib.h>

int main()
{
    InitWindow(800, 640, "Tower Defense");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update
        
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw

        EndDrawing();
    }

    CloseWindow();

    return 0;
}