#include <iostream>
#include <string>

#include "lib.hpp"

#include "intro/raylib_intro.h"
#include "intro/raylib_cpp_intro.h"
#include "intro/benlib_intro.h"


auto main() -> int
{
  auto const lib = library {};
  auto const message = "Hello from " + lib.name + "!";
  std::cout << message << '\n';

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - raylib logo animation");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    play_intro_raylib(screenWidth, screenHeight);
    play_intro_raylib_cpp(screenWidth, screenHeight);
    play_intro_benlib(screenWidth, screenHeight);

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------


  return 0;
}
