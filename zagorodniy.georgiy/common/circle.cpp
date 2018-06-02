#include "circle.hpp"
#include <iostream>
#include <cmath>

using namespace zagorodniy;

Circle::Circle(const point_t & center, const double rad):
  pos_(center) {
  if (rad >= 0.0) {
    radius_ = rad;
  }
  else {
    throw std::invalid_argument("Wrong parameters");
  }
}

double Circle::getArea() const {
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const {
  return rectangle_t{pos_, 2.0 * radius_, 2.0 * radius_};
}

void Circle::move(const point_t & newCenter) {
  pos_ = newCenter;
}

void Circle::move(const double dx, const double dy) {
  pos_.x += dx;
  pos_.y += dy;
}

void Circle::scale(double coef) {
  if (coef < 0.0) {
    throw std::invalid_argument("Wrong coefficient");
  }
  else {
    radius_ *= coef;
  }
}
