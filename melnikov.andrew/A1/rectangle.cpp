#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const point_t & pos, const double width, const double height):
  Shape(pos) {
  if (width < 0.0) {
    throw std::invalid_argument("Width is invalid!");
  } else if (height < 0.0) {
    throw std::invalid_argument("Height is invalid!");
  }
  width_ = width;
  height_ = height;
};

double Rectangle::getArea() const {
  return width_ * height_;
};

rectangle_t Rectangle::getFrameRect() const {
  return rectangle_t{width_, height_, pos_};
};

void Rectangle::move(const double dx, const double dy) {
    pos_.x += dx;
    pos_.y += dy;
};
void Rectangle::move(const point_t & pos) {
  pos_ = pos;
};
