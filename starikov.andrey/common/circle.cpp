#include <iostream>
#include <cmath>
#include "circle.hpp"

using namespace starikov;

Circle::Circle(const double &radius, const point_t centre):
  radius_(radius),
  centre_(centre)
{
  if (radius_ < 0.0)
  {
    throw std::invalid_argument("Warning! Incorrect values...");
  }
  constCentre_ = centre;
}
double Circle::getArea() const noexcept
{
  return M_PI * radius_ * radius_;
}
rectangle_t Circle::getFrameRect() const noexcept
{
  return {radius_ * 2, radius_ * 2, centre_};
}
void Circle::move(const point_t &centre) noexcept
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
void Circle::scale(const double ratio)
{
  if (ratio < 0.0)
  {
    throw std::invalid_argument("Warning! Incorrect ratio...");
  }
  radius_ *= ratio;
}
void Circle::rotate(const double angleDeg)
{
  angleDeg_ += angleDeg;
  if (angleDeg_ >= 360)
  {
    angleDeg_ = fmod(angleDeg_,360);
  }
}
