/*******************************************************************************************
*
*   project_name
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "game.h"
#include "colors.h"
#include <iostream>


#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif


//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------
//Camera camera = { 0 };
//Vector3 cubePosition = { 0 };

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void UpdateDrawFrame(void);          // Update and draw one frame

Font font;
Game game;

double lastUpdateTime = 0;
bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(500, 620, "raylib Tetris");

    font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    game = Game();

    //camera.position = { 3.1f, 3.0f, 2.0f };
    //camera.target = { 0.0f, 0.0f, 0.0f };
    //camera.up = { 0.0f, 1.0f, 0.0f };
    //camera.fovy = 60.0f;
    //camera.projection = CAMERA_PERSPECTIVE;

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

// Update and draw game frame
static void UpdateDrawFrame(void)
{
//    // Update
//    //----------------------------------------------------------------------------------
//    UpdateCamera(&camera, CAMERA_ORBITAL);
//    //----------------------------------------------------------------------------------
//
//    // Draw
//    //----------------------------------------------------------------------------------
//    BeginDrawing();
//
//        ClearBackground(RAYWHITE);
//
//        BeginMode3D(camera);
//
//            DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
//            DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
//            DrawGrid(10, 1.0f);
//
//        EndMode3D();
//
//        DrawText("Welcome to raylib basic sample", 10, 40, 20, DARKGRAY);
//
//    DrawFPS(10, 10);
//
// 
//   EndDrawing();
//    //----------------------------------------------------------------------------------

        UpdateMusicStream(game.music);
        game.HandleInput();
        if (EventTriggered(0.2))
        {
            game.MoveBlockDown();
        }

        BeginDrawing();
        ClearBackground(darkBlue);
        DrawTextEx(font, "Score", { 365, 15 }, 38, 2, WHITE);
        DrawTextEx(font, "Next", { 370, 175 }, 38, 2, WHITE);
        if (game.gameOver)
        {
            DrawTextEx(font, "GAME OVER", { 320, 450 }, 38, 2, WHITE);
        }
        DrawRectangleRounded({ 320, 55, 170, 60 }, 0.3, 6, lightBlue);

        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawTextEx(font, scoreText, { 320 + (170 - textSize.x) / 2, 65 }, 38, 2, WHITE);
        DrawRectangleRounded({ 320, 215, 170, 180 }, 0.3, 6, lightBlue);
        game.Draw();

        DrawFPS(9, 10);

        EndDrawing();
}
