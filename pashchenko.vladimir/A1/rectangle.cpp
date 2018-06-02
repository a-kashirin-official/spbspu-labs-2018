#include "rectangle.hpp"

Rectangle::Rectangle(const point_t &position, const double &width, const double &height) : 
  width_(width), 
  height_(height),
  currPos_(position)
{
  assert(width_ > 0.0);
  assert(height_ > 0.0);
}

void Rectangle::move(const point_t &newP)
{
  currPos_ = newP;
}

void Rectangle::move(const double &nX, const double &nY)
{
  currPos_.x += nX;
  currPos_.y += nY;
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {currPos_, width_, height_};
}
