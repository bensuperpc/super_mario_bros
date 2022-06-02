#ifndef BENLIB_MARIO_HPP
#define BENLIB_MARIO_HPP

#include "direction.h"
#include "entity.hpp"

namespace benlib
{

class Mario : public Entity
{
private:
public:
  Mario() {}

  Mario(::Texture* texture)
      : benlib::Entity(texture)
  {
    // raylib::Texture::Update(texture);
  }

  Mario(::Image* image)
      : benlib::Entity(image)
  {
    // raylib::Texture::Update(image);
  }

  ~Mario() {}

  void update()
  {
    if (this->is_gravity_affected) {
      this->y += this->gravity;
    }
  }
};

}  // namespace benlib

#endif