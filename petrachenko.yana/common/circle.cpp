#include "circle.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace petrachenko;

Circle::Circle(const double radius, const point_t &center):
  radius_(radius),
  center_(center)
{
  if (radius < 0.0)
  {
    throw std::invalid_argument("Invalid_circle_radius");
  }
}

double Circle::getArea() const
{
  return (M_PI * pow(radius_, 2));
}

rectangle_t Circle::getFrameRect() const
{
  return { 2 * radius_, 2 * radius_, center_};
}

void Circle::move(const point_t &p)
{
  center_ = p;
}

void Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

point_t Circle::getPos() const
{
  return (center_);
}

void Circle::scale(double coefficient)
{
  if (coefficient < 0.0)
  {
    throw std::invalid_argument("Invalid_scale_coefficient_for_circle");
  }
  radius_ *= coefficient;
}

void Circle::rotate(double /*alpha*/)
{

}

void Circle::print() const
{
  std::cout << "Circle:" << std::endl;
  std::cout << "Radius is " << radius_ << std::endl;
  std::cout << "Center is (" << getPos().x
  << "," << getPos().y << ")" << std::endl;
  std::cout << "Width of the frame is " << getFrameRect().width << std::endl;
  std::cout << "Height of the frame is " << getFrameRect().height << std::endl;
  std::cout << "Center of the frame is (" << getFrameRect().pos.x
  << "," << getFrameRect().pos.y << ")" << std::endl;
  std::cout << "Area is " << getArea() << std::endl;
  std::cout << std::endl;
}

