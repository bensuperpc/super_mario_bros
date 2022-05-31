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

class Sprite : public raylib::Rectangle, public raylib::Texture
{
private:
  raylib::Rectangle texture_source_rect;
  const float rotation = 0.0;

  const raylib::Vector2 origin = {0, 0};

  raylib::Color tint = {255, 255, 255, 255};
  uint64_t id = 0;

  bool is_visible = true;
  bool draw_bounding_box = false;

public:
  //Sprite() {}

  Sprite(::Texture* texture) : raylib::Rectangle(0, 0, texture->width, texture->height), raylib::Texture(*texture) 
  {
    texture_source_rect = raylib::Rectangle(0, 0, texture->width, texture->height);
  }

  Sprite(::Texture* texture, raylib::Rectangle texture_source_rect, raylib::Rectangle dest) : raylib::Rectangle(dest), raylib::Texture(*texture) 
  {
    this->texture_source_rect = texture_source_rect;
  }
  

/*
  Sprite(const raylib::Image& image)
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

  Sprite(std::string_view path)
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

  Sprite(const std::string & path)
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

  ~Sprite() {}

  void Draw()
  {
    if (is_visible) {
      this->raylib::Texture::Draw(this->texture_source_rect, *this, this->origin, this->rotation, this->tint);
    }

    if (draw_bounding_box)
    {
      this->raylib::Rectangle::DrawLines(BLACK, 0.5f);
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

  GETTERSETTER(float, Height, this->raylib::Rectangle::height)
  GETTERSETTER(float, Width, this->raylib::Rectangle::width)
  GETTERSETTER(float, X, this->raylib::Rectangle::x)
  GETTERSETTER(float, Y, this->raylib::Rectangle::y)

  GETTERSETTER(uint64_t, Id, id)
  GETTERSETTER(::Color, Tint, tint)

  GETTERSETTER(bool, IsVisible, is_visible)
  GETTERSETTER(bool, DrawBoundingBox, draw_bounding_box)

};

}  // namespace benlib

#endif  // BENLIB_SPRITE_HPP
