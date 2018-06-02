#include "rectangle.hpp"

#include <stdexcept>
#include <math.h>

korichev::Rectangle::Rectangle(const korichev::point_t & new_coord, double h, double w):
  coord_(new_coord), h_(h), w_(w), angle_(0.0)
{
  if ((h < 0.0) || (w < 0.0)) {
    h_ = 0.0;
    w_ = 0.0;
    throw std::invalid_argument("Height and Width must be > 0!");
  }
}

double korichev::Rectangle::getArea() const
{
  return h_ * w_;
}

korichev::rectangle_t korichev::Rectangle::getFrameRect() const
{
  double width = abs(w_ * cos(angle_ * M_PI / 180)) + abs(h_ * sin(angle_ * M_PI / 180));
  double height =  abs(w_ * sin(angle_ * M_PI / 180)) + abs(h_ * cos(angle_ * M_PI / 180));

  return {width, height, coord_};
}

void korichev::Rectangle::move(double dx, double dy)
{
  coord_.x += dx;
  coord_.y += dy;
}

void korichev::Rectangle::move(const point_t & pos)
{
  coord_ = pos;
}

void korichev::Rectangle::scale(double ratio)
{
  if (ratio <= 0.0) {
    throw std::invalid_argument("Scale ratio must be > 0");
  } else {
    h_ *= ratio;
    w_ *= ratio;
  }
}

void korichev::Rectangle::rotate(double angle)
{
  angle_ += angle;
  if (angle_ >= 360.0) {
    angle_ -= trunc(angle_/360.0)*360.0;
  }
}
