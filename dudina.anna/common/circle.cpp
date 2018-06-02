#include "circle.hpp"
#define _USE_MATH_DEFINES
#include <math.h>



dudina::Circle::Circle(const point_t & pos, const double radius) :
  pos_(pos),
  radius_(radius)
{
  if (radius_ < 0.0)
  {
    throw std::invalid_argument("Radius must be > 0");
  }
}


double dudina::Circle::getArea() const
{
  return M_PI * radius_*radius_;
}

dudina::rectangle_t dudina::Circle::getFrameRect() const
{
  return { 2 * radius_, 2 * radius_ , pos_ };
}

void dudina::Circle::move(const point_t & pos)
{
  pos_ = pos;
}

void dudina::Circle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void dudina::Circle::scale(const double coeff)
{
  if (coeff < 0.0)
  {
    throw std::invalid_argument("Scale coefficient must be > 0");
  }

  radius_ *= coeff;
}

void dudina::Circle::printInformation()
{
  std::cout << "Radius of circle: " << radius_ << std::endl;
  std::cout << "Position of center: {" << pos_.x << "," << pos_.y << "}" << std::endl;
}


