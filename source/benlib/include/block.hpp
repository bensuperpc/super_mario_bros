#ifndef BENLIB_BLOCK_HPP
#define BENLIB_BLOCK_HPP

#include "sprite.hpp"

namespace benlib
{

class Block : public benlib::Sprite
{
private:
  bool is_solid = true;

public:
  Block() {}

  Block(::Texture* texture)
      : benlib::Sprite(texture)
  {
  }

  Block(::Texture* texture,
        raylib::Rectangle texture_source_rect,
        raylib::Rectangle dest)
      : benlib::Sprite(texture, texture_source_rect, dest)
  {
  }

  ~Block() {}
};

}  // namespace benlib

#endif