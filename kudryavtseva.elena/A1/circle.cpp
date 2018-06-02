#include <cmath>
#include <iostream>
#include "circle.hpp"

Circle::Circle(const point_t & circleCenter, const double r):
  centerCircle_(circleCenter),
  r_(r)
{
  if (r < 0)
  {
    std::cerr << "Error. Invalid radius." << std::endl;
  }
}

double Circle::getArea () const
{
  return r_*r_*M_PI;
}

rectangle_t Circle::getFrameRect () const
{
  return {r_*2, r_*2, centerCircle_};
}

void Circle::move (double dx, double dy)
{
  centerCircle_.x += dx;
  centerCircle_.y += dy;
}

void Circle::move (const point_t &center)
{
  centerCircle_ = center;
}

void Circle::printf()
{
  rectangle_t rect = getFrameRect();
  std::cout << "New coordinates of the center after moving to the point: " << centerCircle_.x << "  " << centerCircle_.y << std::endl;
  std::cout << "Width and height of the rectangle: " << rect.width << "  " << rect.height << std::endl;
  std::cout << "Area: " << Circle::getArea() << std::endl;
}

point_t Circle::getPos()
{
  return centerCircle_;
}
