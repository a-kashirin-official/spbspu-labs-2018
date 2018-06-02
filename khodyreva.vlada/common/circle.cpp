#include "circle.hpp"
#include <cmath>
#include <stdexcept>

using namespace khodyreva;

Circle::Circle(const point_t & pos, double radius):
  radius_(radius),
  pos_(pos)
{
  if (radius < 0.0)
  {
    throw std::invalid_argument("Error. Radius must not be less than 0");
  }
}

double Circle::getArea() const
{
  return radius_*radius_*M_PI;
}

rectangle_t Circle::getFrameRect() const
{
  return{pos_, radius_*2, radius_*2};
}

void Circle::move(const point_t & pos)
{
  pos_ = pos;
}

void Circle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void Circle::scale(const double ratio)
{
  if (ratio <= 0.0)
  {
    throw std::invalid_argument("Wrong input data, ratio must be greater than 0");
  }
  radius_ *= ratio;
}

void Circle::rotate(double /*angle*/)
{

}

std::string Circle::getName() const
{
  return "Circle";
}
