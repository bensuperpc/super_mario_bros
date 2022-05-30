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

class sprite : public raylib::Rectangle, public raylib::Texture
{
private:
  raylib::Rectangle texture_source_rect;

  raylib::Vector2 speed = {0, 0};
  const float rotation = 0.0;

  const raylib::Vector2 origin = {0, 0};

  raylib::Color tint = {255, 255, 255, 255};
  uint64_t id = 0;

  bool is_visible = true;
  bool draw_bounding_box = false;

public:
  sprite() {}

  sprite(::Texture* texture) : raylib::Rectangle(0, 0, texture->width, texture->height), raylib::Texture(*texture) 
  {
    texture_source_rect = raylib::Rectangle(0, 0, texture->width, texture->height);
  }

/*
  sprite(raylib::Texture* texture, raylib::Rectangle texture_source_rect, raylib::Rectangle dest)
      : raylib::Rectangle(dest), texture(texture), texture_source_rect(texture_source_rect) {}

  sprite(const raylib::Image& image)
  {
    this->texture = new raylib::Texture(image);
    this->texture_source_rect = raylib::Rectangle {0,
                                           0,
                                           static_cast<float>(texture->width),
                                           static_cast<float>(texture->height)};
    this->raylib::Rectangle::x = 0;
    this->raylib::Rectangle::y = 0;
    this->raylib::Rectangle::width = static_cast<float>(image.width);
    this->raylib::Rectangle::height = static_cast<float>(image.height);
  }

  sprite(std::string_view path)
  {
    this->texture = new raylib::Texture(path.data());
    this->texture_source_rect = raylib::Rectangle {0,
                                           0,
                                           static_cast<float>(texture->width),
                                           static_cast<float>(texture->height)};
    this->raylib::Rectangle::x = 0;
    this->raylib::Rectangle::y = 0;
    this->raylib::Rectangle::width = static_cast<float>(texture->width);
    this->raylib::Rectangle::height = static_cast<float>(texture->height);
  }

  sprite(const std::string & path)
  {
    this->texture = new raylib::Texture(path.data());
    this->texture_source_rect = raylib::Rectangle {0,
                                           0,
                                           static_cast<float>(texture->width),
                                           static_cast<float>(texture->height)};
    this->raylib::Rectangle::x = 0;
    this->raylib::Rectangle::y = 0;
    this->raylib::Rectangle::width = static_cast<float>(texture->width);
    this->raylib::Rectangle::height = static_cast<float>(texture->height);
  }
  */

  ~sprite() {}

  void Draw()
  {
    this->raylib::Texture::Draw(this->texture_source_rect, *this, this->origin, this->rotation, this->tint);

    if (draw_bounding_box)
    {
      this->raylib::Rectangle::DrawLines(BLACK);
    }
  }

  void Move()
  {
    this->raylib::Rectangle::x += speed.x;
    this->raylib::Rectangle::y += speed.y;
  }

  void Move(const float x, const float y)
  {
    this->raylib::Rectangle::x += x;
    this->raylib::Rectangle::y += y;
  }

  void Move(const ::Vector2& v)
  {
    this->raylib::Rectangle::x += v.x;
    this->raylib::Rectangle::y += v.y;
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

  GETTERSETTER(::Rectangle, SourceRect, texture_source_rect)

  inline ::Vector2 GetPosition() const
  {
    ::Vector2 vec = {this->raylib::Rectangle::x, this->raylib::Rectangle::y};
    return vec;
  }

  inline void SetPosition(::Vector2 value)
  {
    this->raylib::Rectangle::x = value.x;
    this->raylib::Rectangle::y = value.y;
  }

  GETTERSETTER(::Vector2, Speed, speed)
  GETTERSETTER(uint64_t, Id, id)
  GETTERSETTER(::Color, Tint, tint)

  GETTERSETTER(bool, IsVisible, is_visible)
  GETTERSETTER(bool, DrawBoundingBox, draw_bounding_box)

};

}  // namespace benlib

#endif  // BENLIB_SPRITE_HPP
