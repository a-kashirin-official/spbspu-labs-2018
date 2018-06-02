#include <iostream>
#include <cmath>
#include <stdexcept>
#include "circle.hpp"

using namespace xiezhuang;

Circle::Circle(const point_t &pos, double radius):
  pos_(pos),
  radius_(radius)
{
  if (radius < 0.0)
  {
    throw std::invalid_argument("invalid_radius");
  }
}

point_t Circle::getPosition() const
{
  return pos_;
}

double Circle::getRadius() const
{
  return radius_;
}

void Circle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void Circle::move(const point_t &pos)
{
  pos_ = pos;
}

void Circle::scale(double factor)
{
  if (factor <= 0.0)
  {
    throw std::invalid_argument("invalid_scale");
  }
  
  radius_ *= factor;
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {pos_, 2 * radius_, 2 * radius_};
}

void Circle::printInfo() const
{
  std::cout << "center = (" << pos_.x << ", " << pos_.y << ")" << std::endl
    << "radius = " << radius_ << std::endl;
}
