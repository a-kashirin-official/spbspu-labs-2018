#include "circle.hpp"
#include <cmath>
#include <stdexcept>

using namespace almukhametov;

Circle::Circle(double r, point_t c):
  radius_(r),
  center_(c)
{
  if(r < 0.0)
  {
    throw std::invalid_argument("Radius must be >= 0");
  }
}

double Circle::getArea() const
{
  return M_PI*radius_*radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return{2*radius_, 2*radius_, center_};
}

void Circle::move(point_t c)
{
  center_ = c;
}

void Circle::move(double dx, double dy)
{
  center_.y += dy;
  center_.x += dx;
}

void Circle::scale(double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Factor must be >= 0");
  }
  radius_ *= factor;
}
