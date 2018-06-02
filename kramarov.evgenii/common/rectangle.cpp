#include "rectangle.hpp"
#include <stdexcept>

using namespace kramarov;

Rectangle::Rectangle(const double height, const double width, const point_t & center):
  height_(height),
  width_(width),
  center_(center)
{
  if ((height < 0.0) || (width < 0.0))
  {
    throw std::invalid_argument ("Such rectangle doesn't exist");
  }
}

double Rectangle::getArea() const
{
  return height_ * width_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {center_,width_,height_};
}

void Rectangle::move (const point_t & newLocation)
{
  center_ = newLocation;
}

void Rectangle::move (const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Rectangle::scale (const double scaleRate)
{
  if (scaleRate < 0.0)
  {
    throw std::invalid_argument ("Scale rate must be above 0");
  }
  height_ *= scaleRate;
  width_ *= scaleRate;
}

point_t kramarov::Rectangle::getXY() const
{
  return getFrameRect().pos;
}
