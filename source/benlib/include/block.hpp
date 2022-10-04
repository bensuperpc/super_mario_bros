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

  Block(raylib::Texture* texture)
      : benlib::Sprite(texture)
  {
  }

  ~Block() {}
};

}  // namespace benlib

#endif