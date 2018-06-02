#include "circle.hpp"
#include <cmath>
#include <stdexcept>
using namespace babintseva;

Circle::Circle(const point_t &position, const double radius):
    pos_(position),
    radius_(radius)
{
  if (radius < 0.0)
  {
    throw std::invalid_argument("Radius must be >= 0!");
  }
}

bool babintseva::operator==(const Circle &cir1, const Circle &cir2)
{
  if (cir1.pos_.x == cir2.pos_.x &&
      cir1.pos_.y == cir2.pos_.y &&
      cir1.radius_ == cir2.radius_)
  {
    return true;
  }
  else
  {
    return false;
  }
}

std::string Circle::getName() const
{
  return "Circle";
}

double Circle::getArea() const
{
  return(M_PI * radius_ * radius_);
}

void Circle::move(const point_t &pos)
{
  pos_ = pos;
}

void Circle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

rectangle_t Circle::getFrameRect() const
{
  return {pos_, 2 * radius_, 2 * radius_};
}

double Circle::getRadius()
{
  return radius_;
}

void Circle::scale(double ratio)
{
  if (ratio < 0.0)
  {
    throw std::invalid_argument("Ratio can't be < 0!");
  }

  radius_ *= ratio;
}

point_t Circle::getPos() const
{
  return pos_;
}