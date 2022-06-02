#ifndef BENLIB_LEVEL_HPP
#define BENLIB_LEVEL_HPP

#include <string>
#include <string_view>
#include <vector>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "block.hpp"
#include "raylib-cpp.hpp"
#include "raylib.h"
#include "sprite.hpp"

namespace benlib
{

class Level
{
private:
  uint64_t id = 0;

public:
  std::vector<std::unique_ptr<Block>> blocks;

  Level() {}

  ~Level()
  {
    for (auto& block : blocks) {
      block.reset();
      block.release();
    }

    blocks.clear();
    blocks.shrink_to_fit();
  }

  void AddBlock()
  {
    blocks.emplace_back(std::make_unique<Block>());
  }

  void AddBlock(Block* block)
  {
    this->blocks.push_back(std::unique_ptr<Block>(block));
  }

  void Draw()
  {
    for (auto& block : this->blocks) {
      block->Draw();
    }
  }

  bool CheckCollision(benlib::Sprite* entity)
  {
    for (auto& block : this->blocks) {
      // if (CheckCollisionRecs(*block.get(), *entity)) {
      if (entity->CheckCollision(*block.get())) {
        return true;
      }
    }
    return false;
  }
};

}  // namespace benlib

#endif