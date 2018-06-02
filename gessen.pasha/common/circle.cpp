#include "circle.hpp"
#include <stdexcept>
#include <iostream>
#include <cmath>

using namespace gessen;

Circle::Circle(const point_t & center,const double radius):
  center_(center),
  radius_(radius)
{
  if (radius_ < 0.0)
  {
    throw std::invalid_argument("Error. Radius must be equal or greater than zero");
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{center_, 2*radius_, 2*radius_};
}

void Circle::move(const point_t & newCenter)
{
  center_ = newCenter;
}

void Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Circle::scale(const double ScaleCoefficient)
{
  if (ScaleCoefficient < 0.0)
  {
    throw std::invalid_argument("Error. Scale coefficient must be equal or greater than zero");
  }
  radius_ *= ScaleCoefficient;
}

void Circle::rotate(const double /*angle*/)
{
  
}

void Circle::printShapeName() const
{
  std::cout << "Circle" << std::endl;
  std::cout << "width:" << getFrameRect().width << std::endl;
  std::cout << "height:" << getFrameRect().height << std::endl;
  std::cout << "Area:" << getArea() << std::endl;
  std::cout << "pos(x):" << getFrameRect().pos.x << std::endl;
  std::cout << "pos(y):" << getFrameRect().pos.y << std::endl;
}

