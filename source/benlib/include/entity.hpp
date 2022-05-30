#include <string>
#include <string_view>

#include "sprite.hpp"

namespace benlib
{

class entity : public benlib::sprite
{
private:
bool is_alive = true;

public:

entity(::Texture* texture) : benlib::sprite(texture) 
{

}

/*

entity(raylib::Texture* texture, raylib::Rectangle texture_source_rect, raylib::Rectangle dest) : benlib::sprite(texture, texture_source_rect, dest) 
{

}

entity(const raylib::Image& image) : benlib::sprite(image)
{

}

entity(std::string_view path) : benlib::sprite(path)
{

}

*/


~entity()
{
}

};

}; // namespace benlib