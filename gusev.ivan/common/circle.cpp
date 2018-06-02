#include "circle.hpp"
#include <stdexcept>
#include <cmath>

gusev::Circle::Circle(double radius, const point_t &pos):
  radius_(radius),
  center_(pos)
{
  if (radius <= 0)
  {
    throw std::invalid_argument("Invalid argument");
  }
}

double gusev::Circle::getArea() const
{
  return M_PI * pow(radius_, 2);
}

gusev::rectangle_t gusev::Circle::getFrameRect() const
{
  return {radius_ * 2, radius_ * 2, center_};
}

gusev::point_t gusev::Circle::getCenter() const
{
  return center_;
}

void gusev::Circle::move(const point_t &newPoint)
{
  center_ = newPoint;
}

void gusev::Circle::move(const double dx,const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void gusev::Circle::scale(const double coef)
{
  if (coef <= 0)
  {
    throw std::invalid_argument("Invalid coef");
  }
  radius_ *= coef;
}
