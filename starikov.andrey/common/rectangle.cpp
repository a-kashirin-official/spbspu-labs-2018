#include <iostream>
#include <cmath>
#include "rectangle.hpp"

using namespace starikov;

Rectangle::Rectangle(const rectangle_t modelRect):
modelRect_(modelRect)
{
  if ((modelRect_.height < 0.0) || (modelRect_.width < 0.0))
  {
    throw std::invalid_argument("Warning! Incorrect values...");
  }
  constModelRect_ = modelRect_;
  angleDeg_ = 0;
}
double Rectangle::getArea() const noexcept
{
  return (modelRect_.width * modelRect_.height);
}
rectangle_t Rectangle::getFrameRect() const noexcept
{
  return modelRect_;
}
void Rectangle::move(const point_t &centre) noexcept
{
  modelRect_.pos = constModelRect_.pos;
  modelRect_.pos = centre;
}
void Rectangle::move(const double offsetAxisX, const double offsetAxisY)
{
  modelRect_.pos = constModelRect_.pos;
  modelRect_.pos.x += offsetAxisX;
  modelRect_.pos.y += offsetAxisY;
}
void Rectangle::scale(const double ratio)
{
  if (ratio < 0.0)
  {
    throw std::invalid_argument("Warning! Incorrect ratio...");
  }
  modelRect_.height *= ratio;
  modelRect_.width *= ratio;
}
void Rectangle::rotate(const double angleDeg)
{
  if (angleDeg < 0)
  {
    throw std::invalid_argument("Warning! Angle must be positive!");
  }
  angleDeg_ += angleDeg;
  if (angleDeg_ >= 360)
  {
    angleDeg_ = fmod(angleDeg_,360);
  }
  double angleRad = angleDeg_ * M_PI / 180;
  modelRect_.width = constModelRect_.width * fabs(cos(angleRad)) + constModelRect_.height * fabs(sin(angleRad));
  modelRect_.height = constModelRect_.width * fabs(sin(angleRad)) + constModelRect_.height * fabs(cos(angleRad));
}
