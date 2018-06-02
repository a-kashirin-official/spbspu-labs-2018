#include <cmath>
#include <iostream>
#include "rectangle.hpp"

using namespace revtova;

Rectangle::Rectangle(const point_t & pos, const double width, const double height):
  pos_(pos),
  width_(width),
  height_(height),
  angle_(0.0)
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
  const double sint = sin(angle_ * M_PI / 180);
  const double cost = cos(angle_ * M_PI / 180);
  const double width = height_ * abs(sint) + width_ * abs(cost);
  const double height = height_ * abs(cost) + width_ * abs(sint);
  return {width,height,pos_};
}
void Rectangle::scale(const double kscale)
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
void Rectangle::move(const double dx,const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}
void revtova::Rectangle::rotate(const double angle)
{
  angle_ += angle;
  if (angle_ >= 360)
  {
    angle_ = fmod(angle_, 360.0);
  }
}
