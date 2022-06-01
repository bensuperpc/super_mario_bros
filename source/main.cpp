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
#include "raylib-cpp.hpp"

void updatePlayer(benlib::Entity* player,
                  float frameTime,
                  const benlib::Level* level);

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

  benlib::Entity player(&logo);

  // player.SetSourceRect(raylib::Rectangle {4, 52, 32, 16});
  // player.Resize(32, 16);

  player.SetPosition(raylib::Vector2 {0, -48});
  // player.SetDrawBoundingBox(true);
  player.SetSpeed(raylib::Vector2 {4.0, 4.0});

  raylib::Image image_ground_texture(asset_path
                                     + "sprite sheets/blocks/Block.png");
  raylib::Texture ground_texture(image_ground_texture);

  for (int i = 0; i < 64; ++i) {
    for (int j = 0; j < 2; ++j) {
      auto block = new benlib::Block(&ground_texture);
      // auto block = std::make_unique<benlib::Block>(&ground_texture);

      block->SetPosition(raylib::Vector2 {i * 16, j * 16});
      block->SetSourceRect(raylib::Rectangle {4, 340, 16, 15});
      block->Resize(16, 16);
      level.AddBlock(block);
    }
  }

  benlib::Block ground(&ground_texture);
  ground.SetSourceRect(raylib::Rectangle {4, 340, 16, 15});
  ground.Resize(32, 32);
  // ground.SetDrawBoundingBox(true);

  Vector2 mousePosition = {0.0f, -0.0f};
  // Image imageBunny = LoadImageFromMemory(".png", wabbit_alpha_png,
  // wabbit_alpha_png_len); Texture2D texBunny =
  // LoadTextureFromImage(imageBunny);

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

    updatePlayer(&player, frameTime, &level);

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

    level.Draw();

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

    /*
    DrawRectangle(10, 10, 250, 113, Fade(SKYBLUE, 0.5f));
    DrawRectangleLines(10, 10, 250, 113, BLUE);

    DrawText("Free 2d camera controls:", 20, 20, 10, BLACK);
    DrawText("- Right/Left to move Offset", 40, 40, 10, DARKGRAY);
    DrawText("- Mouse Wheel to Zoom in-out", 40, 60, 10, DARKGRAY);
    DrawText("- A / S to Rotate", 40, 80, 10, DARKGRAY);
    DrawText("- R to reset Zoom and Rotation", 40, 100, 10, DARKGRAY);
    */

    EndDrawing();
  }

  // CloseWindow();  // Close window and OpenGL context

  return 0;
}

void updatePlayer(benlib::Entity* player,
                  float frameTime,
                  const benlib::Level* level)
{
  if (IsKeyDown(KEY_Z) || IsKeyDown(KEY_UP))
    player->Move(Direction::UP, frameTime, level);
  if (IsKeyDown(KEY_Q) || IsKeyDown(KEY_LEFT))
    player->Move(Direction::LEFT, frameTime, level);
  if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
    player->Move(Direction::DOWN, frameTime, level);
  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    player->Move(Direction::RIGHT, frameTime, level);
}
