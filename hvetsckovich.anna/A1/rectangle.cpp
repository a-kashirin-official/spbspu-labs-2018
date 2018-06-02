#include "rectangle.hpp"

#include <stdexcept>

Rectangle::Rectangle(const point_t & pos, const double width, const double height):
   pos_(pos),
   width_(width),
   height_(height)
{
  if (width < 0.0)
  {
    throw std::invalid_argument("Width must be > 0");
  }
  if (height < 0.0)
  {
    throw std::invalid_argument("Height must be > 0");
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return { pos_, width_, height_ };
}

void Rectangle::move(const point_t & pos)
{
  pos_ = pos;
}

void Rectangle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}
