#include "rectangle.hpp"

#include <stdexcept>

Rectangle::Rectangle(const point_t & new_coord, double h, double w):
  coord_(new_coord), h_(h), w_(w)
{
  if ((h < 0.0) || (w < 0.0)) {
    h_ = 0.0;
    w_ = 0.0;
    throw std::invalid_argument("Height and Width must be > 0!");
  }
}

double Rectangle::getArea() const
{
  return h_ * w_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {w_, h_, coord_};
}

void Rectangle::move(double dx, double dy)
{
  coord_.x += dx;
  coord_.y += dy;
}

void Rectangle::move(const point_t & pos)
{
  coord_ = pos;
}
