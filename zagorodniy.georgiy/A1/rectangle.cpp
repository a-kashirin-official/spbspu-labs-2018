#include "rectangle.hpp"
#include <iostream>
#include <cassert>

Rectangle::Rectangle(const point_t & center, const double wdt, const double hgh):
  pos(center) {
    assert((wdt >= 0.0) && (hgh >= 0.0));
    width = wdt;
    height = hgh;
}

double Rectangle::getArea() const {
  return(height * width);
}

rectangle_t Rectangle::getFrameRect() const {
  return rectangle_t{width, height, pos};
}

void Rectangle::move(const point_t & newCenter) {
  pos = newCenter;
}

void Rectangle::move(const double dx, const double dy) {
  pos.x += dx;
  pos.y += dy;
}
