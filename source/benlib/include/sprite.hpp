#ifndef BENLIB_SPRITE_HPP
#define BENLIB_SPRITE_HPP

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "raylib-cpp.hpp"
#include "raylib.h"
#include "raylib.hpp"

namespace benlib
{

class sprite
{
private:
  raylib::Texture* texture;
  raylib::Rectangle source_rect;
  raylib::Rectangle dest_rect;

  raylib::Rectangle bounds;
  raylib::Vector2 speed = {0, 0};
  float rotation = 0.0;

  raylib::Color tint = {255, 255, 255, 255};
  uint64_t id = 0;

public:
  sprite() = delete;

  sprite(raylib::Texture* texture)
  {
    this->texture = texture;
    this->source_rect = raylib::Rectangle {0,
                                           0,
                                           static_cast<float>(texture->width),
                                           static_cast<float>(texture->height)};
    this->dest_rect = raylib::Rectangle {0,
                                         0,
                                         static_cast<float>(texture->width),
                                         static_cast<float>(texture->height)};
    this->bounds = raylib::Rectangle {0,
                                      0,
                                      static_cast<float>(texture->width),
                                      static_cast<float>(texture->height)};
  }

  sprite(const raylib::Image& image)
  {
    this->texture = new raylib::Texture(image);
    this->source_rect = raylib::Rectangle {0,
                                           0,
                                           static_cast<float>(texture->width),
                                           static_cast<float>(texture->height)};
    this->dest_rect = raylib::Rectangle {0,
                                         0,
                                         static_cast<float>(texture->width),
                                         static_cast<float>(texture->height)};
    this->bounds = raylib::Rectangle {0,
                                      0,
                                      static_cast<float>(texture->width),
                                      static_cast<float>(texture->height)};
  }

  sprite(std::string_view path)
  {
    this->texture = new raylib::Texture(path.data());
    this->source_rect = raylib::Rectangle {0,
                                           0,
                                           static_cast<float>(texture->width),
                                           static_cast<float>(texture->height)};
    this->dest_rect = raylib::Rectangle {0,
                                         0,
                                         static_cast<float>(texture->width),
                                         static_cast<float>(texture->height)};
    this->bounds = raylib::Rectangle {0,
                                      0,
                                      static_cast<float>(texture->width),
                                      static_cast<float>(texture->height)};
  }

  ~sprite() {}

  void Draw()
  {
    const raylib::Vector2 origin = {0, 0};
    DrawTexturePro(*texture, source_rect, dest_rect, origin, rotation, tint);
    bounds.DrawLines(BLACK);
  }

  bool CheckCollision(const sprite& other)
  {
    return CheckCollisionRecs(this->bounds, other.bounds);
  }

  bool CheckTextureCollision(const sprite& other)
  {
    return CheckCollisionRecs(this->dest_rect, other.dest_rect);
  }

  bool CheckCollision(const raylib::Rectangle& other)
  {
    return CheckCollisionRecs(this->bounds, other);
  }
  
  bool CheckCollision(::Vector2 point) const {
      return ::CheckCollisionPointRec(point, bounds);
  }


  void Move()
  {
    dest_rect.SetX(speed.x + dest_rect.GetX());
    dest_rect.SetY(speed.y + dest_rect.GetY());

    bounds.SetX(dest_rect.GetX());
    bounds.SetY(dest_rect.GetY());
  }

  void Move(const float x, const float y)
  {
    dest_rect.SetX(x + dest_rect.GetX());
    dest_rect.SetY(y + dest_rect.GetY());

    bounds.SetX(dest_rect.GetX());
    bounds.SetY(dest_rect.GetY());
  }

  void Move(const ::Vector2& v)
  {
    dest_rect.SetX(v.x + dest_rect.GetX());
    dest_rect.SetY(v.y + dest_rect.GetY());

    bounds.SetX(dest_rect.GetX());
    bounds.SetY(dest_rect.GetY());
  }

  GETTERSETTER(::Texture, Texture, *texture)
  GETTERSETTER(::Rectangle, SourceRect, source_rect)
  GETTERSETTER(::Rectangle, DestRect, dest_rect)

  // GETTERSETTER(::Vector2, Position, position)

  inline ::Vector2 GetPosition() const
  {
    ::Vector2 vec = {dest_rect.GetX(), dest_rect.GetY()};
    return vec;
  }
  inline void SetPosition(::Vector2 value)
  {
    source_rect.SetX(value.x);
    source_rect.SetY(value.y);
  }

  GETTERSETTER(::Rectangle, Bounds, bounds)
  GETTERSETTER(::Vector2, Speed, speed)
  GETTERSETTER(uint64_t, Id, id)
  GETTERSETTER(float, Rotation, rotation)
  GETTERSETTER(::Color, Tint, tint)
};

}  // namespace benlib

#endif  // BENLIB_SPRITE_HPP
