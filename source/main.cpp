#include <iostream>
#include <string>

#include "lib.hpp"

#include "intro/raylib_intro.h"
#include "intro/raylib_cpp_intro.h"
#include "intro/benlib_intro.h"

#include "raylib-cpp.hpp"

#include "sprite.hpp"


auto main() -> int
{
  auto const lib = library {};
  auto const message = "Hello from " + lib.name + "!";
  std::cout << message << '\n';

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;

    raylib::Window window(screenWidth, screenHeight, "raylib [shapes] example - raylib logo animation");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // play_intro_raylib(screenWidth, screenHeight);
    // play_intro_raylib_cpp(screenWidth, screenHeight);
    // play_intro_benlib(screenWidth, screenHeight);

    const std::string asset_path = "../3rd-party/smb_assset-src/";

    raylib::Texture logo(asset_path + "sprite sheets/creatures/mario/Mario.png");

    benlib::sprite mario(&logo);

    /*
    Image imageBunny =
      LoadImageFromMemory(".png", wabbit_alpha_png, wabbit_alpha_png_len);
    Texture2D texBunny = LoadTextureFromImage(imageBunny);
    */

    SetTargetFPS(60);

    while (!window.ShouldClose())
    {

        if (IsKeyDown(KEY_RIGHT)) mario.Move(4.0, 0);
        if (IsKeyDown(KEY_LEFT)) mario.Move(-4.0, 0);
        if (IsKeyDown(KEY_UP))  mario.Move(0, -4.0);
        if (IsKeyDown(KEY_DOWN)) mario.Move(0, 4.0);


        BeginDrawing();
        window.ClearBackground(RAYWHITE);
        mario.Draw();

        EndDrawing();
    }


    // De-Initialization
    //--------------------------------------------------------------------------------------
    // CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------


  return 0;
}
