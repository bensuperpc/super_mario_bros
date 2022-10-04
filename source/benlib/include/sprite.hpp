#ifndef BENLIB_SPRITE_HPP
#define BENLIB_SPRITE_HPP

#include <string>
#include <string_view>
#include <vector>

#include "raylib-cpp.hpp"
#include "raylib.h"

namespace benlib
{

class Sprite : public raylib::Rectangle
{
protected:
  raylib::Texture* texture = nullptr;

  float rotation = 0.0f;
  raylib::Color tint = {255, 255, 255, 255};
  raylib::Vector2 origin = {0, 0};
  raylib::Rectangle source_rect = {0, 0, 0, 0};

  bool is_enable = true;
  bool is_visible = true;
  bool draw_bounding_box = false;

private:
  uint64_t id = 0;

public:
  Sprite() {}

  Sprite(raylib::Texture* texture)
      : raylib::Rectangle(0, 0, texture->width, texture->height)
  {
    this->texture = texture;
    this->source_rect = raylib::Rectangle(
        0.0, 0.0, (float)texture->width, (float)texture->height);
  }

  Sprite(raylib::Texture* texture, raylib::Rectangle dest)
      : raylib::Rectangle(dest)
  {
    this->texture = texture;
    this->source_rect = raylib::Rectangle(
        0.0, 0.0, (float)texture->width, (float)texture->height);
  }

  ~Sprite() {}

  void Draw()
  {
    if (this->is_enable) {
      if (this->is_visible) {
        this->texture->Draw(
            this->source_rect, *this, origin, this->rotation, this->tint);
      }

      if (true) {
        this->raylib::Rectangle::DrawLines(BLACK, 0.5f);
      }
    }
  }

  void Resize(const float width, const float height)
  {
    this->raylib::Rectangle::width = width;
    this->raylib::Rectangle::height = height;
  }

  void Resize(const ::Vector2& v)
  {
    this->raylib::Rectangle::width = v.x;
    this->raylib::Rectangle::height = v.y;
  }

  GETTERSETTER(raylib::Texture*, Texture, texture)

  GETTERSETTER(float, Height, this->raylib::Rectangle::height)
  GETTERSETTER(float, Width, this->raylib::Rectangle::width)
  GETTERSETTER(float, X, this->raylib::Rectangle::x)
  GETTERSETTER(float, Y, this->raylib::Rectangle::y)

  GETTERSETTER(uint64_t, Id, id)
  GETTERSETTER(raylib::Color, Tint, tint)
  GETTERSETTER(float, Rotation, rotation)
  GETTERSETTER(raylib::Rectangle, SourceRect, source_rect)
  GETTERSETTER(raylib::Vector2, Origin, origin)

  GETTERSETTER(bool, IsEnable, is_enable)
  GETTERSETTER(bool, IsVisible, is_visible)
  GETTERSETTER(bool, DrawBoundingBox, draw_bounding_box)
};

}  // namespace benlib

#endif  // BENLIB_SPRITE_HPP
