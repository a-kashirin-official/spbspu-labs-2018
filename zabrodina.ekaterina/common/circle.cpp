#include "circle.hpp"

#include <iostream>
#include <cmath>

zabrodina::Circle::Circle(const point_t &position, const double rad):
  center_(position),
  radius_(rad)
{
  if (radius_ <= 0)
  {
    throw std::invalid_argument("Error: Radius <= 0");
  }
}

double zabrodina::Circle::getArea() const
{
  return M_PI*radius_*radius_;
}

zabrodina::rectangle_t zabrodina::Circle::getFrameRect() const
{
  return {radius_ * 2,radius_ * 2, center_};
}

void zabrodina::Circle::move(const point_t &position)
{
  center_ = position;
}

void zabrodina::Circle::move(const double Ox, const double Oy)
{
  center_.x += Ox;
  center_.y += Oy;
}

void zabrodina::Circle::printInf() const
{
  std::cout << "Area of a circle: " << Circle::getArea() << std::endl;
  std::cout << "Radius of a circle: " << radius_ << std::endl;
  std::cout << "Center of a circle: (" << center_.x << "," << center_.y <<")" << std::endl;
  rectangle_t frame = getFrameRect();
  std::cout << "Frame Center (" << frame.pos.x << "," << frame.pos.y << ")" << std::endl;
  std::cout << "Frame Width: " << frame.width << "   Frame Height: " << frame.height << std::endl;
}

void zabrodina::Circle::scale(const double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Error: coefficient <= 0");
  }
  else
  {
    radius_ *= coefficient;
  }
}
