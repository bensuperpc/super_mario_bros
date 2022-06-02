#ifndef BENLIB_ENTITY_HPP
#define BENLIB_ENTITY_HPP

#include <array>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "direction.h"
#include "level.hpp"
#include "sprite.hpp"

namespace benlib
{

class Entity : public benlib::Sprite
{
protected:
  raylib::Vector2 speed = {0, 0};
  float gravity = 2.0;
  bool is_gravity_affected = true;

  Direction spriteDirection = Direction::LEFT;

public:
  Entity()
      : benlib::Sprite()
  {
  }

  Entity(::Texture* texture)
      : benlib::Sprite(texture)
  {
  }

  Entity(::Texture* texture,
         raylib::Rectangle texture_source_rect,
         raylib::Rectangle dest)
      : benlib::Sprite(texture, texture_source_rect, dest)
  {
  }

  Entity(::Image* image)
      : benlib::Sprite(image)
  {
  }

  /*

  Entity(std::string_view path) : benlib::Sprite(path)
  {

  }
  */

  ~Entity() {}

  void update()
  {
    if (this->is_gravity_affected) {
      this->y += this->gravity;
    }
  }

  void Move(const Direction direction,
            const float frameTime,
            const benlib::Level* level)
  {
    if (this->is_enable) {
      switch (direction) {
        case Direction::UP: {
          auto newPoseY = this->y - this->speed.y;
          const raylib::Rectangle collisionEdge =
              calculateEdge(direction, this->x, newPoseY);

          for (auto& block : level->blocks) {
            if (CheckCollisionRecs(*block.get(), collisionEdge)) {
              ResolveCollision(direction, this->x, newPoseY, block.get());
            }
          }
          this->y = newPoseY;
          spriteDirection = Direction::UP;
          break;
        }
        case Direction::DOWN: {
          auto newPoseY = this->y + this->speed.y;
          const raylib::Rectangle collisionEdge =
              calculateEdge(direction, this->x, newPoseY);

          for (auto& block : level->blocks) {
            if (CheckCollisionRecs(*block.get(), collisionEdge)) {
              ResolveCollision(direction, this->x, newPoseY, block.get());
            }
          }
          this->y = newPoseY;
          spriteDirection = Direction::DOWN;
          break;
        }
        case Direction::RIGHT: {
          auto newPoseX = this->x + this->speed.x;
          const raylib::Rectangle collisionEdge =
              calculateEdge(direction, newPoseX, this->y);

          for (auto& block : level->blocks) {
            if (CheckCollisionRecs(*block.get(), collisionEdge)) {
              ResolveCollision(direction, newPoseX, this->y, block.get());
            }
          }
          this->x = newPoseX;
          spriteDirection = Direction::RIGHT;
          break;
        }
        case Direction::LEFT: {
          auto newPoseX = this->x - this->speed.x;
          const raylib::Rectangle collisionEdge =
              calculateEdge(direction, newPoseX, this->y);

          for (auto& block : level->blocks) {
            if (CheckCollisionRecs(*block.get(), collisionEdge)) {
              ResolveCollision(direction, newPoseX, this->y, block.get());
            }
          }
          this->x = newPoseX;
          spriteDirection = Direction::LEFT;
          break;
        }
      }
    }
  }

  void ResolveCollision(const Direction direction,
                        float& xPosition,
                        float& yPosition,
                        const benlib::Sprite* sprite)
  {
    int topLeftX_i = static_cast<int>(xPosition);
    int topLeftY_i = static_cast<int>(yPosition);

    switch (direction) {
      case Direction::UP:
        yPosition = sprite->GetY() + sprite->GetHeight();
        break;
      case Direction::DOWN:
        yPosition = sprite->GetY() - this->raylib::Rectangle::height;
        break;
      case Direction::RIGHT:
        xPosition = sprite->GetX() - this->raylib::Rectangle::width;
        break;
      case Direction::LEFT:
        xPosition = sprite->GetX() + sprite->GetHeight();

        break;
    }
  }

  raylib::Rectangle calculateEdge(const Direction direction,
                                  const float xPosition,
                                  const float yPosition) const
  {
    switch (direction) {
      case Direction::UP:
        return {xPosition,
                yPosition,
                this->raylib::Rectangle::width,
                this->raylib::Rectangle::height};
      case Direction::DOWN:
        return {xPosition,
                yPosition,
                this->raylib::Rectangle::width,
                this->raylib::Rectangle::height};
      case Direction::RIGHT:
        return {xPosition,
                yPosition,
                this->raylib::Rectangle::width,
                this->raylib::Rectangle::height};
      case Direction::LEFT:
        return {xPosition,
                yPosition,
                this->raylib::Rectangle::width,
                this->raylib::Rectangle::height};
    }
    return {0, 0, 0, 0};
  }

  GETTERSETTER(::Vector2, Speed, speed)

  GETTERSETTER(float, Gravity, gravity)
  GETTERSETTER(bool, IsGravityAffected, is_gravity_affected)
  GETTERSETTER(Direction, SpriteDirection, spriteDirection)
};

};  // namespace benlib

#endif