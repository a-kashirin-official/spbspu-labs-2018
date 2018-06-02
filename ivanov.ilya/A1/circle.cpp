#include "circle.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

Circle::Circle(const point_t & center, double r):
  center_(center),
  radius_(r)
{
  if (r < 0.0)
  {
    throw std::invalid_argument("Raduis can`t be negative");
  }
}

void Circle::show() const
{
  std::cout << "Object of circle: " << "\n";
  std::cout << "Area = " << getArea() << ", Radius = " << radius_ << "\n";
  rectangle_t border = getFrameRect();
  std::cout << "X coord: " << border.pos.x << ", Y coord: " << border.pos.y;
  std::cout << ", width = " << border.width << ", height = " <<border.height << "\n";
}

double Circle::getArea() const
{
  return M_PI*(radius_*radius_);
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{center_, radius_*2, radius_*2};
}

void Circle::move (const point_t & movement)
{
  center_ = movement;
}

void Circle::move (double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}
