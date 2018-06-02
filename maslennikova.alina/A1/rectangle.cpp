#include "rectangle.hpp"

Rectangle::Rectangle(const point_t & center,const double h,const double w):
  pos(center)
{
  if ((h > 0) && (w > 0)){
    height = h;
    width = w;
  }
}

double Rectangle::getArea() const {
  return width * height;
}

rectangle_t Rectangle::getFrameRect() const {
  return rectangle_t{width, height, pos};
}

void Rectangle::move(const point_t & newCenter) {
  pos  = newCenter;
}

void Rectangle::move(const double dx, const double dy) {
  pos.x += dx;
  pos.y += dy;
}
