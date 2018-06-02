#include "rectangle.hpp"
#include <cmath>
#include <stdexcept>

ivanov::Rectangle::Rectangle(const point_t & centr, double height, double width):
  rec_ {centr, height, width}
{
  if ((height < 0.0) || (width < 0.0))
  {
    throw std::invalid_argument ("ERROR");
  }
}

ivanov::rectangle_t ivanov::Rectangle::getFrameRect() const
{
  return rec_;
}

double ivanov::Rectangle::getArea() const
{
  return rec_.height * rec_.width;
}

void ivanov::Rectangle::move(const point_t & pos)
{
  rec_.pos = pos;
}

void ivanov::Rectangle::move(double dx, double dy)
{
  rec_.pos.x += dx;
  rec_.pos.y += dy;
}

void ivanov::Rectangle::scale(double k)
{
  if (k < 0.0)
  {
    throw std::invalid_argument ("ERROR");
  }
  rec_.height *= k;
  rec_.width *= k;
}
