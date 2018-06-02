#include "rectangle.hpp"
#include <iostream>

using namespace zagorodniy;

Rectangle::Rectangle(const point_t & center, const double wdt, const double hgh):
  pos_(center) {
    if ((wdt >= 0.0) && (hgh >= 0.0)) {
      width_ = wdt;
      height_ = hgh;
    }
    else {
      throw std::invalid_argument("Wrong parameters");
    }
}

double Rectangle::getArea() const {
  return(height_ * width_);
}

rectangle_t Rectangle::getFrameRect() const {
  return rectangle_t{pos_, width_, height_};
}

void Rectangle::move(const point_t & newCenter) {
  pos_ = newCenter;
}

void Rectangle::move(const double dx, const double dy) {
  pos_.x += dx;
  pos_.y += dy;
}

void Rectangle::scale(double coef) {
  if (coef < 0.0) {
    throw std::invalid_argument("Wrong coefficient");
  }
  else {
    width_ *= coef;
    height_ *= coef;
  }
}
