#include "rectangle.hpp"
#include <iostream>

brusnitsyna::Rectangle::Rectangle(const rectangle_t & rect):
  rect_(rect)
{
  if (rect.width < 0.0 || rect.height < 0.0) {
    throw std::invalid_argument("Invalid rectangle height or width");
  }
}

double brusnitsyna::Rectangle::getArea() const
{
  return rect_.width * rect_.height;
}

brusnitsyna::rectangle_t brusnitsyna::Rectangle::getFrameRect() const
{
  return rect_;
}

void brusnitsyna::Rectangle::move(const point_t & pos)
{
  rect_.pos = pos;
}

void brusnitsyna::Rectangle::move(double dx, double dy)
{
  rect_.pos.x += dx;
  rect_.pos.y += dy;
}

void brusnitsyna::Rectangle::scale(double k)
{
  if (k < 0.0) {
    throw std::invalid_argument("Invalid k");
  }
  rect_.width *= k;
  rect_.height *= k;
}
