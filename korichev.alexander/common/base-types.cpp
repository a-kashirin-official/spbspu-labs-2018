#include "base-types.hpp"
#include "cmath"

bool korichev::rectangle_t::cross( const korichev::rectangle_t & rect)
{
  bool cross_x = false;
  bool cross_y = false;

  if (std::abs(this->pos.y - rect.pos.y) <= ( this->height / 2 + rect.height / 2 ) ) {
    cross_y = true;
  }
  if (std::abs(this->pos.x - rect.pos.x) <= ( this->width / 2 + rect.width / 2 ) ) {
    cross_x = true;
  }
  return (cross_x && cross_y);

}
