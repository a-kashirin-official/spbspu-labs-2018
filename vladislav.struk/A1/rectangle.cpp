#include "rectangle.hpp"
#include <stdexcept>

Rectangle::Rectangle(const point_t &pos,double height,double width):
  pos_(pos),
  width_(width),
  height_(height)
{
  if ((width < 0) || (height < 0))
  {
    throw std::invalid_argument("Height and width must be nonnegative");
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {pos_.x,pos_.y,width_,height_};
}

void Rectangle::move(const point_t &pos)
{
  pos_= pos;
}

void Rectangle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}



