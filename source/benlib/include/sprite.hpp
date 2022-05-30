#ifndef BENLIB_SPRITE_HPP
#define BENLIB_SPRITE_HPP

#include <string>
#include <string_view>
#include <vector>

#include "raylib-cpp.hpp"
#include "raylib.h"
#include "raylib.hpp"

namespace benlib
{

class sprite : public raylib::Rectangle
{
private:
  raylib::Texture* texture;
  raylib::Rectangle texture_source_rect;

  raylib::Vector2 speed = {0, 0};
  float rotation = 0.0;

  raylib::Color tint = {255, 255, 255, 255};
  uint64_t id = 0;

public:
  sprite() {}

  sprite(raylib::Texture* texture)
  {
    this->texture = texture;
    this->texture_source_rect = raylib::Rectangle {0,
                                           0,
                                           static_cast<float>(texture->width),
                                           static_cast<float>(texture->height)};
    this->x = 0;
    this->y = 0;
    this->width = static_cast<float>(texture->width);
    this->height = static_cast<float>(texture->height);
  }

  sprite(raylib::Texture* texture, raylib::Rectangle texture_source_rect, raylib::Rectangle dest)
  {
    this->texture = texture;
    this->texture_source_rect = texture_source_rect;
    this->x = dest.x;
    this->y = dest.y;
    this->width = dest.width;
    this->height = dest.height;
  }

  


  sprite(const raylib::Image& image)
  {
    this->texture = new raylib::Texture(image);
    this->texture_source_rect = raylib::Rectangle {0,
                                           0,
                                           static_cast<float>(texture->width),
                                           static_cast<float>(texture->height)};
    this->x = 0;
    this->y = 0;
    this->width = static_cast<float>(image.width);
    this->height = static_cast<float>(image.height);
  }

  sprite(std::string_view path)
  {
    this->texture = new raylib::Texture(path.data());
    this->texture_source_rect = raylib::Rectangle {0,
                                           0,
                                           static_cast<float>(texture->width),
                                           static_cast<float>(texture->height)};
    this->x = 0;
    this->y = 0;
    this->width = static_cast<float>(texture->width);
    this->height = static_cast<float>(texture->height);
  }

  ~sprite() {}

  void Draw()
  {
    const raylib::Vector2 origin = {0, 0};
    DrawTexturePro(*texture, texture_source_rect, *this, origin, rotation, tint);
    this->DrawLines(BLACK);
  }

  void Move()
  {
    this->x += speed.x;
    this->y += speed.y;
  }

  void Move(const float x, const float y)
  {
    this->x += x;
    this->y += y;
  }

  void Move(const ::Vector2& v)
  {
    this->x += v.x;
    this->y += v.y;
  }

  GETTERSETTER(::Texture, Texture, *texture)
  GETTERSETTER(::Rectangle, SourceRect, texture_source_rect)

  inline ::Vector2 GetPosition() const
  {
    ::Vector2 vec = {this->x, this->y};
    return vec;
  }

  inline void SetPosition(::Vector2 value)
  {

    this->x = value.x;
    this->y = value.y;
  }

  GETTERSETTER(::Vector2, Speed, speed)
  GETTERSETTER(uint64_t, Id, id)
  GETTERSETTER(float, Rotation, rotation)
  GETTERSETTER(::Color, Tint, tint)
};

}  // namespace benlib

#endif  // BENLIB_SPRITE_HPP
