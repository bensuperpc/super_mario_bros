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
  Mario()
      : Entity()
  {
  }

  Mario(raylib::Texture* texture)
      : Entity(texture)
  {
  }

  Mario(raylib::Texture* texture, raylib::Rectangle dest)
      : Entity(texture, dest)
  {
  }

  ~Mario() {}

  void updatePlayer(float frameTime, const benlib::Level* level)
  {
    if (IsKeyDown(KEY_Z) || IsKeyDown(KEY_UP)) {
      this->Move(Direction::UP, frameTime, level);
    }
    if (IsKeyDown(KEY_Q) || IsKeyDown(KEY_LEFT)) {
      if (this->GetDirection() != Direction::LEFT) {
        auto&& sourceRect = this->GetSourceRect();
        sourceRect.width = -1 * sourceRect.width;
        this->SetSourceRect(sourceRect);
      }
      this->Move(Direction::LEFT, frameTime, level);
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
      this->Move(Direction::DOWN, frameTime, level);
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
      if (this->GetDirection() != Direction::RIGHT) {
        auto&& sourceRect = this->GetSourceRect();
        sourceRect.width = std::abs(sourceRect.width);
        this->SetSourceRect(sourceRect);
      }
      this->Move(Direction::RIGHT, frameTime, level);
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

  void update()
  {
    if (this->is_gravity_affected) {
      this->y += this->gravity;
    }
  }
};

}  // namespace benlib

#endif