#include "triangle.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>

Triangle::Triangle(const point_t & a, const point_t & b, const point_t & c):
  Shape({((a.x + b.x + c.x) / 3.0), ((a.y + b.y + c.y) / 3.0)}) {
  double ab = sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
  double bc = sqrt(pow(c.x - b.x, 2) + pow(c.y - b.y, 2));
  double ac = sqrt(pow(c.x - a.x, 2) + pow(c.y - a.y, 2));

  if (ab + bc <= ac) {
    throw std::invalid_argument("Points of triangle are invalid! AB + BC <= AC");
  } else if (ab + ac <= bc) {
    throw std::invalid_argument("Points of triangle are invalid! AB + AC <= BC");
  } else if (ac + bc <= ab) {
    throw std::invalid_argument("Points of triangle are invalid! AC + BC <= AB");
  }
  a_ = a;
  b_ = b;
  c_ = c;
};

double Triangle::getArea() const {
  return abs(0.5 * ((a_.x - c_.x) * (b_.y - c_.y) 
                    - (b_.x - c_.x) * (a_.y - c_.y)));
};

rectangle_t Triangle::getFrameRect() const {
  double width = std::max(std::max(a_.x, b_.x), c_.x) 
                 - std::min(std::min(a_.x, b_.x), c_.x);
  double height = std::max(std::max(a_.y, b_.y), c_.y) 
                  - std::min(std::min(a_.y, b_.y), c_.y);
  double plus_to_X = width / 2.0 - (pos_.x - std::min(std::min(a_.x, b_.x), c_.x));
  double plus_to_Y = height / 2.0 - (pos_.y - std::min(std::min(a_.y, b_.y), c_.y));
  return rectangle_t{width, height, {pos_.x + plus_to_X, pos_.y + plus_to_Y}};
};

void Triangle::move(const double dx, const double dy) {
  a_.x += dx;
  a_.y += dy;
  b_.x += dx;
  b_.y += dy;
  c_.x += dx;
  c_.y += dy;
  pos_.x += dx;
  pos_.y += dy;
};

void Triangle::move(const point_t & pos) {
  a_.x -= pos_.x - pos.x;
  a_.y -= pos_.y - pos.y;
  b_.x -= pos_.x - pos.x;
  b_.y -= pos_.y - pos.y;
  c_.x -= pos_.x - pos.x;
  c_.y -= pos_.y - pos.y;
  pos_ = pos;
};
