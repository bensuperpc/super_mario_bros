#ifndef BENLIB_SPRITE_HPP
#define BENLIB_SPRITE_HPP

#include <iostream>
#include <string>
#include <vector>

#include "raylib-cpp.hpp"
#include "raylib.h"
#include "raylib.hpp"

namespace benlib
{

class sprite
{
private:

  raylib::Texture texture;
  raylib::Rectangle source_rect;
  raylib::Rectangle dest_rect;
  raylib::Vector2 origin = {0, 0};


  raylib::Rectangle bounds;
  raylib::Vector2 speed = {0, 0};
  float rotation = 0.0;

  raylib::Color tint = {255, 255, 255, 255};
  uint64_t id = 0;

public:
  //sprite() {}

  sprite(const ::Texture texture)
  {
    this->texture = texture;
    this->source_rect = raylib::Rectangle{0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height)};
    this->dest_rect = raylib::Rectangle{0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height)};
    this->bounds = raylib::Rectangle{0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height)};
  }

  ~sprite() {
      // UnloadTexture(texture);
  }

  void Draw()
  {
    DrawTexturePro(texture,
                   source_rect,
                   dest_rect,
                   origin,
                   rotation,
                   tint);
  }

  bool CheckCollision(const sprite &other)
  {
    return CheckCollisionRecs(this->bounds, other.bounds);
  }

  bool CheckTextureCollision(const sprite &other)
  {
    //TODO
    return CheckCollisionRecs(this->dest_rect, other.dest_rect);
  }

  void Move()
  {
    origin.x += speed.x;
    origin.y += speed.y;
  }

  void Move(const float x, const float y)
  {
    origin.x += x;
    origin.y += y;
  }

  void Move(const ::Vector2& v)
  {
    origin.x += v.x;
    origin.y += v.y;
  }

  //GETTERSETTER(::Texture, Texture, texture)
  GETTERSETTER(::Rectangle, SourceRect, source_rect)
  GETTERSETTER(::Rectangle, DestRect, dest_rect)

  GETTERSETTER(::Vector2, Origin, origin)
  GETTERSETTER(::Vector2, Position, origin)


  GETTERSETTER(::Rectangle, Bounds, bounds)
  GETTERSETTER(::Vector2, Speed, speed)
  GETTERSETTER(uint64_t, Id, id)
  GETTERSETTER(float, Rotation, rotation)
  GETTERSETTER(::Color, Tint, tint)
  
  };

}  // namespace benlib

#endif  // BENLIB_SPRITE_HPP
