#include "circle.hpp"
#include <iostream>
#include <cmath>
#include <cassert>

Circle::Circle(const point_t & center, const double rad):
  pos(center) {
  assert(rad >= 0.0);
  radius = rad;
}

double Circle::getArea() const {
  return M_PI * radius * radius;
}

rectangle_t Circle::getFrameRect() const {
  return rectangle_t{2 * radius, 2 * radius, pos};
}

void Circle::move(const point_t & newCenter) {
  pos = newCenter;
}

void Circle::move(const double dx, const double dy) {
  pos.x += dx;
  pos.y += dy;
}
