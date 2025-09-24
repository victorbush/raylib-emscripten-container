#include "raylib.h"
#include "raymath.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

using namespace std;

/* ----------------------------------------------------------------------------
Constants
----------------------------------------------------------------------------- */

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;

/* ----------------------------------------------------------------------------
Variables
----------------------------------------------------------------------------- */

Camera2D camera;

Texture2D catTexture;
float catX = (SCREEN_WIDTH / 2);
float catY = (SCREEN_HEIGHT / 2);

/* ----------------------------------------------------------------------------
Functions
----------------------------------------------------------------------------- */

void UpdateDrawFrame(void)
{
    /* ------------------------------------------------------------------------
    Update frame

    Run any logic to compute the state of this frame, such
    as user input, game state, and physics computations.
    ------------------------------------------------------------------------- */

    if (IsKeyDown(KEY_RIGHT)) {
        catX += 2.0f;
    }
    else if (IsKeyDown(KEY_LEFT)) {
        catX -= 2.0f;
    }

    if (IsKeyDown(KEY_UP)) {
        catY -= 2.0f;
    }
    else if (IsKeyDown(KEY_DOWN)) {
        catY += 2.0f;
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        catX = GetMouseX();
        catY = GetMouseY();
    }

    /* ------------------------------------------------------------------------
    Draw frame

    Draw any objects in the world or text on the screen based on their current
    position/state.
    ------------------------------------------------------------------------- */

    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode2D(camera);

    // Draw the cat
    DrawTextureEx(catTexture, { catX, catY }, 0.0f, 1.0f, WHITE);

    EndMode2D();

    EndDrawing();
}

/**
Program entry point.
*/
int main(void)
{
    /* ------------------------------------------------------------------------
    Initialization
    ------------------------------------------------------------------------- */

    // Scale things for high DPI monitors so we can see it
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);

    // Enable anti-aliasing
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    // Setup the application window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Example");

    // Set game to run at 60 frames-per-second
    SetTargetFPS(60);

    // Create a basic 2D camera
    camera.offset = { 0, 0 };
    camera.rotation = 0;
    camera.target = { 0, 0 };
    camera.zoom = 1.0f;

    // Load cat texture
    catTexture = LoadTexture("assets/cat.png");
    if (!catTexture.id)
        throw new runtime_error("Failed to load cat texture.");

    /* ------------------------------------------------------------------------
    Main loop
    ------------------------------------------------------------------------- */

#if defined(PLATFORM_WEB)
    // https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5)#4-setup-raylib-game-for-web
    // 
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    // Close window and OpenGL context
    CloseWindow();

    return 0;
}
