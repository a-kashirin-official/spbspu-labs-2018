#include "rectangle.hpp"
#include <stdexcept>

kadyrov::Rectangle::Rectangle(const kadyrov::rectangle_t &rect) :
  rectangle_(rect)
{
  if (rectangle_.width < 0.0 || rectangle_.height < 0.0)
  {
    throw std::invalid_argument("Wrong value of width or height");
  }
}

double kadyrov::Rectangle::getArea() const
{
  return rectangle_.width * rectangle_.height;
}

kadyrov::rectangle_t kadyrov::Rectangle::getFrameRect() const
{
  return { rectangle_.width , rectangle_.height , rectangle_.pos };
}

void kadyrov::Rectangle::move(const double dx, const double dy)
{
  rectangle_.pos.x += dx;
  rectangle_.pos.y += dy;
}

void kadyrov::Rectangle::move(const point_t &newPos)
{
  rectangle_.pos = newPos;
}

void kadyrov::Rectangle::scale(const double coefficient)
{
  if (coefficient < 0.0)
  {
    throw std::invalid_argument("Wrong value of coefficient!");
  }
  else
  {
    rectangle_.height *= coefficient;
    rectangle_.width *= coefficient;
  }
}
