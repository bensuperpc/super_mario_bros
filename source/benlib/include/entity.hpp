#include <array>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "sprite.hpp"

enum class Direction
{
  NORTH,
  SOUTH,
  EAST,
  WEST
};

const std::array<Direction, 4> ALL_DIRECTIONS = {
    Direction::NORTH, Direction::SOUTH, Direction::EAST, Direction::WEST};

namespace benlib
{

class entity : public benlib::sprite
{
private:
  bool is_alive = true;
  raylib::Vector2 speed = {0, 0};
  float velocity = 4.0;
  float xPositionNew;
  float yPositionNew;

  Direction spriteDirection = Direction::WEST;

public:
  entity(::Texture* texture)
      : benlib::sprite(texture)
  {
  }

  /*
  entity(raylib::Texture* texture, raylib::Rectangle texture_source_rect,
  raylib::Rectangle dest) : benlib::sprite(texture, texture_source_rect, dest)
  {

  }

  entity(const raylib::Image& image) : benlib::sprite(image)
  {

  }

  entity(std::string_view path) : benlib::sprite(path)
  {

  }
  */
  /*
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
  */

  ~entity() {}

  void move(Direction direction, float frameTime, const benlib::sprite& level)
  {
    std::cout << "move" << std::endl;
    switch (direction) {
      case Direction::NORTH: {
        std::cout << "NORTH" << std::endl;
        yPositionNew = this->y - 4.0;

        std::cout << "yPositionNew: " << yPositionNew << std::endl;
        std::cout << "this->y: " << this->y << std::endl;

        if (checkCollision(direction, this->x, yPositionNew, level)) {
          std::cout << "Collision detected" << std::endl;
          resolveCollision(direction, this->x, yPositionNew, level);
        }

        this->y = yPositionNew;
        break;
      }
      case Direction::SOUTH: {
        std::cout << "SOUTH" << std::endl;
        yPositionNew = this->y + 4.0;

        if (checkCollision(direction, this->x, yPositionNew, level)) {
          std::cout << "Collision detected" << std::endl;
          resolveCollision(direction, this->x, yPositionNew, level);
        }
        this->y = yPositionNew;
        break;
      }
      case Direction::EAST: {
        std::cout << "EAST" << std::endl;
        // xPositionNew = this->x + frameTime * velocity;
        xPositionNew = this->x + 4.0;

        if (checkCollision(direction, xPositionNew, this->y, level)) {
          std::cout << "Collision detected" << std::endl;
          resolveCollision(direction, xPositionNew, this->y, level);
        }
        this->x = xPositionNew;
        spriteDirection = Direction::EAST;
        break;
      }
      case Direction::WEST: {
        std::cout << "WEST" << std::endl;
        // xPositionNew = this->x - frameTime * velocity;
        xPositionNew = this->x - 4.0;

        if (checkCollision(direction, xPositionNew, this->y, level)) {
          std::cout << "Collision detected" << std::endl;
          resolveCollision(direction, xPositionNew, this->y, level);
        }
        this->x = xPositionNew;
        spriteDirection = Direction::WEST;
        break;
      }
    }
  }

    void resolveCollision(Direction direction,
                        float topLeftX,
                        float topLeftY,
                        const benlib::sprite& level)
  {
    int topLeftX_i = static_cast<int>(topLeftX);
    int topLeftY_i = static_cast<int>(topLeftY);

    switch (direction) {
      case Direction::NORTH:
      yPositionNew = level.GetY() + level.GetHeight();
      break;
      case Direction::SOUTH:
        yPositionNew = level.GetY() - this->raylib::Rectangle::height;
        break;
      case Direction::EAST:
        xPositionNew = level.GetX() - this->raylib::Rectangle::width;
        break;
      case Direction::WEST:
      xPositionNew = level.GetX() + level.GetHeight();

      break;
    }
  }

  bool checkCollision(Direction direction,
                      float xPosition,
                      float yPosition,
                      const benlib::sprite& level) const
  {
    raylib::Rectangle collisionEdge = calculateEdge(direction, xPosition, yPosition, 1.0f);
    return CheckCollisionRecs(level, collisionEdge);
  }

  raylib::Rectangle calculateEdge(Direction direction,
                     float topLeftX,
                     float topLeftY,
                     float directionOffset) const
  {

      std::cout << "calculateEdge" << std::endl;
      std::cout << "topLeftX: " << topLeftX << std::endl;
      std::cout << "topLeftY: " << topLeftY << std::endl;
    switch (direction) {
      case Direction::NORTH:
        return {topLeftX,
                topLeftY,
                topLeftX + directionOffset * this->raylib::Rectangle::width,
                topLeftY};
      case Direction::SOUTH:
        return {topLeftX,
                topLeftY + this->raylib::Rectangle::height,
                topLeftX + directionOffset * this->raylib::Rectangle::width,
                topLeftY + this->raylib::Rectangle::height};
      case Direction::EAST:
        return {topLeftX + this->raylib::Rectangle::width,
                topLeftY,
                topLeftX + this->raylib::Rectangle::width,
                topLeftY + directionOffset * this->raylib::Rectangle::height};
      case Direction::WEST:
        return {topLeftX,
                topLeftY,
                topLeftX,
                topLeftY + directionOffset * this->raylib::Rectangle::height};
    }
  }

  GETTERSETTER(::Vector2, Speed, speed)
};

};  // namespace benlib