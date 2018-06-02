#include "circle.hpp"
#include <cmath>
#include <stdexcept>

sibikin::Circle::Circle(const point_t & center, const double R):
  r_(R),
  pos_(center)
{
  if (R < 0.0)
  {
    throw std::invalid_argument("radius cannot be < 0");
  }
}

double sibikin::Circle::getArea() const
{
  return r_ * r_ * M_PI;
}

sibikin::rectangle_t sibikin::Circle::getFrameRect() const
{
  return {2*r_, 2*r_, pos_};
}

sibikin::point_t sibikin::Circle::getPos() const
{
  return pos_;
}

void sibikin::Circle::move(const point_t & newCenter)
{
  pos_ = newCenter;
}

void sibikin::Circle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void sibikin::Circle::scale(const double coef)
{
  if (coef > 0.0)
  {
    r_ *= coef;
  }
  else
  {
    throw std::invalid_argument("coef must be > 0");
  }
}

void sibikin::Circle::rotate(const double)
{

}
