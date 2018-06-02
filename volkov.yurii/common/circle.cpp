#include "circle.hpp"
#include <cmath>
#include <stdexcept>

using namespace volkov;

Circle::Circle(const point_t & pos, double radius):
  pos_ (pos),
  radius_(radius)
{
  if (radius < 0.0)
  {
    throw std::invalid_argument("invalid value");
  }
}

double Circle::getRadius() const
{
  return radius_;
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {pos_, radius_ * 2 , radius_ * 2};
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

void Circle::scale(const double f)
{
  if (f < 0.0)
  {
    throw std::invalid_argument("f be sure >= 0");
  }
  radius_ *= f;
}

std::ostream & volkov::operator<<(std::ostream & out, const Circle & circle)
{
  out << "Area: " << circle.getArea() << std::endl;
  out <<"pos (" << circle.getFrameRect().pos.x << ", " << circle.getFrameRect().pos.y << ")" << std::endl;
  out << "radius: " << circle.radius_;

  return out;
}

