/*******************************************************************************************
*
*   raylib [core] example - Basic 3d example
*
*   Welcome to raylib!
*
*   To compile example, just press F5.
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2023 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include "logger.h"
#include "sphere.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif
#include <iostream>
#include <debugapi.h>

//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------
Camera camera = { 0 };
Vector3 cubePosition = { 0 };

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void UpdateDrawFrame(void);          // Update and draw one frame

//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main()
{   
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "raylib");

    camera.position = (Vector3){ 10.0f, 10.0f, 8.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    //--------------------------------------------------------------------------------------

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

FileLogger logger;

bool isPaused = false;
float timestep = 1.f; // timestep in seconds

const Vector3 GLOBAL_UP{0, 1, 0};
const Vector3 GLOBAL_RIGHT{1, 0, 0};
const Vector3 GLOBAL_FORWARD{0, 0, 1};

Sphere s{1.f, 1.f, Vector3{0, 7, 0}, Vector3Zero(), 0.4f, 0.f, 0.f};

static void updateCamera(void) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        UpdateCamera(&camera, CAMERA_FREE);
    } else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) || GetMouseWheelMove() != 0) {
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);
    } else if (IsKeyDown(KEY_C)) {
        camera.target = Vector3Zero();
    }
}

static void updateScene(void) {
    if (IsKeyPressed(KEY_R)) {
        s.reset();
    } else if (IsKeyPressed(KEY_P)) {
        isPaused = !isPaused;
    }
}

static void updateObjects(float deltaTime) {
    if (isPaused) {
        if (IsKeyPressed(KEY_F)) {
            s.update(timestep);
            logger.logToFile("timestep increased");
        }
    } else {
        s.update(deltaTime);
    }
}

// Update and draw game frame
static void UpdateDrawFrame(void)
{
    float deltaTime = GetFrameTime();
    
    // Update
    //----------------------------------------------------------------------------------
    updateCamera();
    updateScene();
    updateObjects(deltaTime);

    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

            //DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
            //DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
            s.draw();

            DrawGrid(50, 1.0f);

        EndMode3D();

        DrawText("Physics Sandbox", 10, 40, 20, DARKGRAY);
        if (isPaused) {
            DrawText("PAUSED", 10, 70, 40, RED);
        }

        DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
}
