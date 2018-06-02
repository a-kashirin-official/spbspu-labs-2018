#include "circle.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

Circle::Circle(const point_t & pos, const double radius) :
  pos_(pos),
  radius_(radius)
{
  if (radius < 0) 
  {
    std::cerr << "Radius must be >0 " << std::endl;
    radius_ = 0;
  }
}

double Circle::getArea() const
{
  return M_PI * radius_*radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return { 2 * radius_, 2 * radius_ , pos_ };
}

void Circle::move(const point_t & pos)
{
  pos_ = pos;
}

void Circle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void Circle::printInformation()
{
  std::cout << "Radius of circle: " << radius_ << std::endl;
  std::cout << "Position of center: {" << pos_.x << "," << pos_.y << "}" << std::endl;
}


