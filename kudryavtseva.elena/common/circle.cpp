#include "circle.hpp"
#include <cmath>
#include <iostream>

kudryavtseva::Circle::Circle(const kudryavtseva::point_t &circleCenter, const double r):
centerCircle_(circleCenter),
r_(r)
{
  if (r < 0.0)
  {
    throw std::invalid_argument("Error. Invalid radius.");
  }
}

double kudryavtseva::Circle::getArea () const
{
  return r_*r_*M_PI;
}

kudryavtseva::rectangle_t kudryavtseva::Circle::getFrameRect () const
{
  return {r_*2.0, r_*2.0, centerCircle_};
}

void kudryavtseva::Circle::move (double dx, double dy)
{
  centerCircle_.x += dx;
  centerCircle_.y += dy;
}

void kudryavtseva::Circle::move (const kudryavtseva::point_t &center)
{
  centerCircle_ = center;
}

void kudryavtseva::Circle::scale (const double k)
{
    std::cout << "Radius before scaling: " << r_ << std::endl;
    if (k < 0.0)
    {
      throw std::invalid_argument("Error. Invalid coefficient.");
    }
    r_*=k;
    std::cout << "Radius after scaling with coefficient " << k << " : " << r_ << std::endl;
}

kudryavtseva::point_t kudryavtseva::Circle::getPos() const
{
  return centerCircle_;
}

void kudryavtseva::Circle::printf() const
{
  kudryavtseva::rectangle_t rect = getFrameRect();
  std::cout << "___FOR THE CIRCLE___" << std::endl;
  std::cout << "Width and height of the rectangle: " << rect.width << "  " << rect.height << std::endl;
  std::cout << "Area: " << getArea() << std::endl;
  std::cout << "Coordinates of the center: " << getPos().x << "  " << getPos().y << std::endl;
  std::cout << "\n" << std::endl;
}

double kudryavtseva::Circle::getRadius() const
{
    return r_;
}

void kudryavtseva::Circle::rotate(double /*angle*/)
{
}
