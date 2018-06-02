#include "rectangle.hpp"
#include <stdexcept>

using namespace mordvintseva;

Rectangle::Rectangle(const rectangle_t & r):
  rect_(r)
{
  if ((rect_.width < 0.0) || (rect_.height < 0.0)) {
    throw std::invalid_argument("The width and height of rectangle must be positive");
  };
};

double Rectangle::getArea() const
{
  return (rect_.width * rect_.height);
};

rectangle_t Rectangle::getFrameRect() const
{
  return rect_;
};

void Rectangle::move(const point_t & point) 
{
  rect_.pos = point;
};

void Rectangle::move(const double dx, const double dy) 
{
  rect_.pos.x += dx;
  rect_.pos.y += dy;
};

void Rectangle::scale(const double factor)
{
  if (factor >= 0.0) {
    rect_.width *= factor;
    rect_.height *= factor;
  } else {
    throw std::invalid_argument("The scaling factor must be non-negative");
  }
}
