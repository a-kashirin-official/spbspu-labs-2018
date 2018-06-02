#include "rectangle.hpp"
#include <stdexcept>

Rectangle::Rectangle(const rectangle_t & rect):
  rect_(rect)
{
  if ((rect_.height < 0.0) || (rect_.width < 0.0))
  {
    throw std::invalid_argument("Error. Invalid height or width of rectangle.");
  }
}

double Rectangle::getArea() const noexcept
{
  return (rect_.width * rect_.height);
}

rectangle_t Rectangle::getFrameRect() const noexcept
{
  return rect_;
}

void Rectangle::move(const point_t & point) noexcept
{
  rect_.pos = point;
}

void Rectangle::move(const double dx, const double dy) noexcept
{
  rect_.pos.x += dx;
  rect_.pos.y += dy;
}
