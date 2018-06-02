#include "rectangle.hpp"

#include <stdexcept>

Rectangle::Rectangle(const point_t & middle, const double width, const double height):
  middle_(middle),
  width_(width),
  height_(height)
{
  if ((width < 0) || (height < 0))
  {
    throw std::invalid_argument("Invalid rectangle");
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {middle_, width_, height_};
}

void Rectangle::move(const point_t & pos)
{
  middle_ = pos;
}

void Rectangle::move(const double dx, const double dy)
{
  middle_.x += dx;
  middle_.y += dy;
}

