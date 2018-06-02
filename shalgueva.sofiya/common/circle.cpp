#include "circle.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

shalgueva::Circle::Circle(const point_t & pos, const double radius) :
  position_(pos),
  radius_(radius),
  angle_(0.0)
{
  if (radius_ < 0.0)
  {
    throw std::invalid_argument("Error. Invalid radius");
  }
}

double shalgueva::Circle::getArea() const noexcept
{
  return M_PI * radius_ * radius_;
}

shalgueva::rectangle_t shalgueva::Circle::getFrameRect() const noexcept
{
  return {radius_ * 2, radius_ * 2, position_};
}

void shalgueva::Circle::move(double dx, double dy) noexcept
{
  position_.x += dx;
  position_.y += dy;
}

void shalgueva::Circle::move(const point_t & posTo) noexcept
{
  position_ = posTo;
}

void shalgueva::Circle::scale(double coefficient)
{
  if (coefficient < 0.0)
  {
    throw std::invalid_argument("Error. Invalid parameter of scaling");
  }
  radius_ *= coefficient;
}

void shalgueva::Circle::rotate(double alpha) noexcept
{
  angle_ += alpha;
  if (angle_ > 360.0)
  {
    angle_ -= 360;
  }
}
