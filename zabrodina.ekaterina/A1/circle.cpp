#include "circle.hpp"

#include <iostream>
#include <cmath>

Circle::Circle(const point_t &position, const double rad):
  center_(position),
  radius_(rad)
{
  if (radius_ <= 0)
  {
    throw std::invalid_argument("Error: Radius <= 0");
  }
}

double Circle::getArea() const
{
  return M_PI*radius_*radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {radius_ * 2,radius_ * 2, center_};
}

void Circle::move(const point_t &position)
{
  center_ = position;
}

void Circle::move(const double Ox, const double Oy)
{
  center_.x += Ox;
  center_.y += Oy;
}

void Circle::printInf()
{
  std::cout << "Area of a circle: " << Circle::getArea() << std::endl;
  std::cout << "Radius of a circle: " << radius_ << std::endl;
  std::cout << "Center of a circle: (" << center_.x << "," << center_.y << ")" << std::endl;
  rectangle_t frame = getFrameRect();
  std::cout << "Frame Center (" << frame.pos.x << "," << frame.pos.y << ")" << std::endl;
  std::cout << "Frame Width: " << frame.width << "   Frame Height: " << frame.height << std::endl;
}
