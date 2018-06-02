#include <iostream>
#include <cmath>
#include "circle.hpp"

Circle::Circle(const double &radius, const point_t centre):
  radius_(radius),
  centre_(centre)
{
  if (radius_ < 0)
  {
    std::cerr << "Warning! Incorrect values..." << std::endl;
  }
  constCentre_ = centre;
}
double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}
rectangle_t Circle::getFrameRect() const
{
  return {radius_ * 2, radius_ * 2, centre_};
}
void Circle::move(const point_t &centre)
{
  centre_ = constCentre_;
  centre_ = centre;
}
void Circle::move(const double offsetAxisX, const double offsetAxisY)
{
  centre_ = constCentre_;
  centre_.x += offsetAxisX;
  centre_.y += offsetAxisY;
}
