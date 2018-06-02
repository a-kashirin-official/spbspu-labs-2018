#include "rectangle.hpp"
#include <cmath>
#include <stdexcept>

using namespace lysenko;

Rectangle::Rectangle(const point_t & rect,const double width,const double heigth):
  center_(rect),
  width_(width),
  heigth_(heigth)
{
  if ((width_ < 0.0) || (heigth_ < 0.0))
  {
    throw::std::invalid_argument("Error! Width and heigth must be >= 0.0");
  }
}

double Rectangle::getArea() const
{
  return (width_ * heigth_);
}

rectangle_t Rectangle::getFrameRect() const
{
  return {center_, width_, heigth_};
}

void Rectangle::move(const point_t & center)
{
  center_ = center;
}

void Rectangle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Rectangle::scale(const double ScaleCoeff)
{
  if (ScaleCoeff < 0.0)
  {
    throw::std::invalid_argument("Error! ScaleCoeff must be >= 0.0");
  }
  width_ *= ScaleCoeff;
  heigth_ *= ScaleCoeff;
}
