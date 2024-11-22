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
//#include "colors.h"
#include <iostream>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

static void UpdateDrawFrame(void);

Font font;
Game* game;

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

int main()
{
    InitWindow(500, 620, "raylib Tetris");

    font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    game = new Game();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }
#endif

    delete game;

    CloseWindow();

    return 0;
}

// Update and draw game frame
static void UpdateDrawFrame(void)
{ 
    //this is bad...
    Color lightBlue = { 59, 85, 162, 255 };
    Color darkBlue = { 44, 44, 127, 255 };

    //UpdateMusicStream(game->music);
    game->HandleInput();
    if (EventTriggered(0.2))
    {
        game->MoveBlockDown();
    }
    
    BeginDrawing();
    ClearBackground(darkBlue);
    
    DrawTextEx(font, "Leo v2", { 320, 550 }, 38, 2, WHITE);
    
    DrawTextEx(font, "Score", { 365, 15 }, 38, 2, WHITE);
    DrawTextEx(font, "Next", { 370, 175 }, 38, 2, WHITE);
    if (game->gameOver)
    {
        DrawTextEx(font, "GAME OVER", { 320, 450 }, 38, 2, WHITE);
    }
    DrawRectangleRounded({ 320, 55, 170, 60 }, 0.3, 6, lightBlue);
    
    char scoreText[10];
    sprintf(scoreText, "%d", game->score);
    Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
    
    DrawTextEx(font, scoreText, { 320 + (170 - textSize.x) / 2, 65 }, 38, 2, WHITE);
    DrawRectangleRounded({ 320, 215, 170, 180 }, 0.3, 6, lightBlue);
    game->Draw();
    
    DrawFPS(10, 10);
    
    EndDrawing();
}
