#include "rectangle.hpp"
#include <iostream>
#include <stdexcept>

using namespace revtova;

Rectangle::Rectangle(const point_t & pos, const double width, const double height):
  pos_(pos),
  width_(width),
  height_(height)
{
  if ((width < 0.0) || (height < 0.0))
  {
    throw std::invalid_argument("Invalid value");
  }
}
double Rectangle::getArea() const
{
  return width_*height_;
}
rectangle_t Rectangle::getFrameRect() const
{
  return {width_,height_,pos_};
}
void Rectangle::scale(double kscale)
{
  if (kscale < 0.0)
  {
    throw std::invalid_argument("Invalid value");
  }
  width_ *= kscale;
  height_ *= kscale;
}
void Rectangle::move(const point_t & pos)
{
  pos_ = pos;
}
void Rectangle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}
