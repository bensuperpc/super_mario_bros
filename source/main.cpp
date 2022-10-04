#include <iostream>
#include <string>
#include <thread>

#include "block.hpp"
#include "entity.hpp"
#include "intro/benlib_intro.h"
#include "intro/raylib_cpp_intro.h"
#include "intro/raylib_intro.h"
#include "level.hpp"
#include "lib.hpp"
#include "mario.hpp"
#include "raylib-cpp.hpp"

auto main() -> int
{
  const int screenWidth = 800;
  const int screenHeight = 450;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);

  raylib::Window window(screenWidth,
                        screenHeight,
                        "raylib [shapes] example - raylib logo animation");

  raylib::AudioDevice audiodevice;

  SetTargetFPS(60);

  play_intro_raylib(screenWidth, screenHeight);
  play_intro_raylib_cpp(screenWidth, screenHeight);
  play_intro_benlib(screenWidth, screenHeight);

  auto level = benlib::Level();

  const std::string asset_path = "../3rd-party/smb_assset-src/";
  raylib::Image image(asset_path + "sprite sheets/creatures/mario/Mario.png");
  image.Crop(4, 52, 32, 16);
  image.RotateCCW();

  raylib::Texture logo(image);

  benlib::Mario player(&logo);

  // player.SetSourceRect(raylib::Rectangle {4, 52, 32, 16});
  // player.Resize(32, 16);

  player.SetPosition(raylib::Vector2 {0, -48});
  // player.SetDrawBoundingBox(true);
  player.SetSpeed(raylib::Vector2 {4.0, 4.0});

  raylib::Image image_ground_texture(asset_path
                                     + "sprite sheets/blocks/Block.png");
  image_ground_texture.Crop(4, 4, 16, 16);

  raylib::Texture ground_texture(image_ground_texture);

  for (int i = 0; i < 64; ++i) {
    for (int j = 0; j < 1; ++j) {
      auto block = new benlib::Block(&ground_texture);
      // auto block = std::make_unique<benlib::Block>(&ground_texture);

      block->SetPosition(raylib::Vector2 {i * 16, j * 16});
      // block->SetSourceRect(raylib::Rectangle {4, 340, 16, 15});
      // block->Resize(16, 16);
      level.AddBlock(block);
    }
  }

  benlib::Block ground(&ground_texture);
  // ground.SetSourceRect(raylib::Rectangle {4, 340, 16, 15});
  ground.Resize(32, 32);
  // ground.SetDrawBoundingBox(true);

  Vector2 mousePosition = {0.0f, -0.0f};

  raylib::Camera2D camera = {};
  camera.target =
      (Vector2) {player.GetX() + player.Rectangle::GetWidth() / 2.0f,
                 player.GetY() + player.Rectangle::GetHeight() / 2.0f};

  camera.offset = (Vector2) {screenWidth / 2.0f, screenHeight / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    float frameTime = GetFrameTime();
    mousePosition = GetMousePosition();

    /*
    if (IsKeyPressed(KEY_F11))
    {
      int display = GetCurrentMonitor();

      if (IsWindowFullscreen()) {
        SetWindowSize(screenWidth, screenHeight);
      } else {
        SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
      }
      ToggleFullscreen();
    }
    */

    player.updatePlayer(frameTime, &level);

    camera.target =
        (Vector2) {player.GetX() + player.Rectangle::GetWidth() / 2.0f,
                   player.GetY() + player.Rectangle::GetHeight() / 2.0f};

    if (IsKeyDown(KEY_A))
      camera.rotation--;
    else if (IsKeyDown(KEY_S))
      camera.rotation++;

    if (camera.rotation > 40)
      camera.rotation = 40;
    else if (camera.rotation < -40)
      camera.rotation = -40;

    camera.zoom += ((float)GetMouseWheelMove() * 0.05f);

    if (IsKeyPressed(KEY_R)) {
      camera.zoom = 1.0f;
      camera.rotation = 0.0f;
    }

    if (camera.zoom > 3.0f)
      camera.zoom = 3.0f;
    else if (camera.zoom < 0.1f)
      camera.zoom = 0.1f;

    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode2D(camera);

    DrawRectangle(-6000, 320, 13000, 8000, DARKGRAY);

    level.Draw();
    player.Draw();

    DrawLine((int)camera.target.x,
             -screenHeight * 10,
             (int)camera.target.x,
             screenHeight * 10,
             GREEN);
    DrawLine(-screenWidth * 10,
             (int)camera.target.y,
             screenWidth * 10,
             (int)camera.target.y,
             GREEN);

    // ground.Draw();

    EndMode2D();

    // std::string fps = std::to_string(GetFPS());

    std::string screenCoordinates = "x: " + std::to_string((int)mousePosition.x)
        + " y: " + std::to_string((int)mousePosition.y);

    DrawText(screenCoordinates.c_str(), 650, 10, 20, RED);

    Vector2 vecWorldCoordinates = camera.GetScreenToWorld(mousePosition);

    std::string WorldCoordinates =
        "x: " + std::to_string((int)vecWorldCoordinates.x)
        + " y: " + std::to_string((int)vecWorldCoordinates.y);

    DrawText(WorldCoordinates.c_str(), 650, 30, 20, RED);
    EndDrawing();
  }

  // CloseWindow();  // Close window and OpenGL context

  return 0;
}
