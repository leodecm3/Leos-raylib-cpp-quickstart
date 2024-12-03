#include "raylib.h"
#include <cmath>

#include "resource_dir.h"
#include "MyClass.h"

  int main () 
  {

    // just prove its working with classes multifile
    MyClass* my = new MyClass();
    int targetWidth = my->TestFunction();
    delete my;

    int height{450};
    // int width{800};
    InitWindow(targetWidth, height, "Wabbit game");

    GetMonitorCount();

    if (GetMonitorCount() > 1) {
        SetWindowMonitor(1); // Play the game on the second monitor
    }

    //SetWindowPosition(int x, int y);

    SearchAndSetResourceDir("resources");

    Texture wabbit = LoadTexture("wabbit_alpha.png");
    Image MyIcon = LoadImage("icon.png");

    SetWindowIcon(MyIcon);
    UnloadImage(MyIcon);

    // circle coordinates
    int circle_x = 200;
    int circle_y = 200;
    int circle_radius = 25;
    // circle edges
    int l_circle_x = circle_x - circle_radius;
    int r_circle_x = circle_x + circle_radius;
    int u_circle_y = circle_y - circle_radius;
    int b_circle_y = circle_y + circle_radius;

    // axe coordinates
    int axe_x = 400;
    int axe_y = 0;
    int axe_length = 50;
    // axe edges
    int l_axe_x = axe_x;
    int r_axe_x = axe_x + axe_length;
    int u_axe_y = axe_y;
    int b_axe_y = axe_y + axe_length;

    int direction = 1; // 1 or -1
    float axeSpeed = 60.0f * 10.0f;
    float wabbitSpeed = 60.0f * 7.5f;

    bool collision_with_axe = 
                        (b_axe_y >= u_circle_y) && 
                        (u_axe_y <= b_circle_y) && 
                        (r_axe_x >= l_circle_x) && 
                        (l_axe_x <= r_circle_x);

    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(WHITE);

        DrawFPS(10, 10);

        DrawText("Use A and D to move the Rabbit", 10, 40, 20, RED);


        if (collision_with_axe)
        {
            DrawText("Game Over!", 400, 200, 20, RED);
        }
        else
        {
            // Game logic begins

            // update the edges
            l_circle_x = circle_x - circle_radius;
            r_circle_x = circle_x + circle_radius;
            u_circle_y = circle_y - circle_radius;
            b_circle_y = circle_y + circle_radius;
            l_axe_x = axe_x;
            r_axe_x = axe_x + axe_length;
            u_axe_y = axe_y;
            b_axe_y = axe_y + axe_length;
            // update collision
            collision_with_axe = 
                        (b_axe_y >= u_circle_y) && 
                        (u_axe_y <= b_circle_y) && 
                        (r_axe_x >= l_circle_x) && 
                        (l_axe_x <= r_circle_x);

            DrawCircle(circle_x, circle_y, circle_radius, BLUE);
            DrawTexture(wabbit, circle_x - 15, circle_y - 15, WHITE);

            DrawRectangle(axe_x, axe_y, axe_length, axe_length, RED);
            DrawTexture(wabbit, axe_x + 10, axe_y + 10, WHITE);

            // move the axe
            const float deltaTime = GetFrameTime();
            axe_y += direction * deltaTime * axeSpeed;

            // Zig zag logic
            const float midPoint = height / 2;
            const float distFromMid = abs( axe_y - midPoint );

            // how far can you go from the mid point before going back
            if (distFromMid > ( height / 2 ))
            { 
                direction *= -1;
            }
            
            if ( circle_x < GetScreenWidth() && ( IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) ) )
            {
                circle_x += deltaTime * wabbitSpeed;
            }
            
            if ( circle_x > 0 && ( IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) ) )
            {
                circle_x -= deltaTime * wabbitSpeed;
            }

            // Game logic ends
        }

        EndDrawing();
    }

    // This is the end of the code; technically, we don't UnloadTexture, but...
    UnloadTexture(wabbit);
}