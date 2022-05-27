#include "lib.hpp"

auto main() -> int
{
  auto const lib = library {};

  return lib.name == "super_mario_bros" ? 0 : 1;
}
