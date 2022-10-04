#ifndef BENLIB_ENTITY_HPP
#define BENLIB_ENTITY_HPP

#include <array>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "direction.h"
#include "sprite.hpp"
#include "level.hpp"

namespace benlib
{

class Entity : public benlib::Sprite
{
protected:
  raylib::Vector2 speed = {0, 0};
  float gravity = 2.0;
  bool is_gravity_affected = true;

  Direction spriteDirection = Direction::RIGHT;

public:
  Entity()
      : benlib::Sprite()
  {
  }

  Entity(raylib::Texture* texture)
      : benlib::Sprite(texture)
  {
  }

  Entity(raylib::Texture* texture, raylib::Rectangle dest)
      : benlib::Sprite(texture, dest)
  {
  }

  ~Entity() {}

  virtual void update()
  {
  }

  virtual void Move(const Direction direction,
            const float frameTime,
            const benlib::Level* level)
  {
  }

  GETTERSETTER(::Vector2, Speed, speed)

  GETTERSETTER(float, Gravity, gravity)
  GETTERSETTER(bool, IsGravityAffected, is_gravity_affected)
  GETTERSETTER(Direction, Direction, spriteDirection)
};

};  // namespace benlib

#endif