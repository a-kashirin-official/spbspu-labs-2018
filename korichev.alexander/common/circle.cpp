#include "circle.hpp"

#include <cmath>
#include <stdexcept>

korichev::Circle::Circle(const korichev::point_t & new_coord, double new_radius):
  coord_(new_coord), radius_(new_radius), angle_(0.0)
{
  if (new_radius < 0.0) {
    radius_ = 0.0;
    throw std::invalid_argument("Radius must be > 0");
  }
}

double korichev::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

korichev::rectangle_t korichev::Circle::getFrameRect() const
{
  return {2 * radius_, 2 * radius_, coord_};
}

void korichev::Circle::move(double dx, double dy)
{
  coord_.x += dx;
  coord_.y += dy;
}

void korichev::Circle::move(const point_t & pos)
{
  coord_ = pos;
}

void korichev::Circle::scale(double ratio)
{
  if (ratio <= 0.0) {
    throw std::invalid_argument("Scale ratio must be > 0");
  } else {
    radius_ *= ratio;
  }
}

void korichev::Circle::rotate(double angle)
{
  angle_ += angle;
  if (angle_ >= 360.0) {
    angle_ -= trunc(angle_/360.0)*360.0;
  }
}
