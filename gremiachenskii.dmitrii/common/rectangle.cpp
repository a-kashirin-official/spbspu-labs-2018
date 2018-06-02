#include "rectangle.hpp"
#include <stdexcept>

using namespace gremiachenskii;

Rectangle::Rectangle(const point_t & center, double height, double width):
  rect_{ center, height, width }
{
  if (height < 0.0 || width < 0.0)
  {
    throw std::invalid_argument("ERROR: Negative rectangle height or width");
  }
}

Rectangle::Rectangle(const rectangle_t & rect):
  rect_(rect)
{
  if (rect.height < 0.0 || rect.width < 0.0)
  {
    throw std::invalid_argument("ERROR: Negative rectangle height or width");
  }
}

void Rectangle::move(const point_t & pos)
{
  rect_.pos = pos;
}

void Rectangle::move(double dx, double dy)
{
  rect_.pos.x += dx;
  rect_.pos.y += dy;
}

double Rectangle::getArea() const
{
  return rect_.height * rect_.width;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rect_;
}

void Rectangle::scale(double ratio)
{
  if (ratio < 0.0)
  {
    throw std::invalid_argument("ERROR: Negative scale ratio");
  }

  rect_.height *= ratio;
  rect_.width *= ratio;
}
