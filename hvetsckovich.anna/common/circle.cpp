#include "circle.hpp"

#include <math.h>
#include <stdexcept>

using namespace hvetsckovich;

hvetsckovich::Circle::Circle(const point_t & pos, const double radius):
  pos_(pos),
  radius_(radius),
  angle_(0.0)
{
  if (radius < 0.0)
  {
    throw std::invalid_argument("Radius must be > 0");
  }
}

point_t hvetsckovich::Circle::getPos() const
{
  return pos_;
}

double hvetsckovich::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t hvetsckovich::Circle::getFrameRect() const
{
  return { pos_, radius_ * 2, radius_ * 2 };
}

double hvetsckovich::Circle::getRadius() const
{
  return radius_;
}

void hvetsckovich::Circle::move(const point_t & pos)
{
  pos_ = pos;
}

void hvetsckovich::Circle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void hvetsckovich::Circle::scale(const double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Scale factor must be > 0");
  }

  radius_ *= factor;
}

void hvetsckovich::Circle::rotate(const double degrees)
{
  angle_ += degrees;
  
  if (angle_ >= 360.0)
  {
    angle_ = fmod(angle_, 360.0);
  }
}
