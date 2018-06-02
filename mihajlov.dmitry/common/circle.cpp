#define _USE_MATH_DEFINES
#include "circle.hpp"
#include <iostream>
#include <cmath>

mihajlov::Circle::Circle(const point_t& centerPos, const double r):
  pos_{centerPos},
  radius_(0.0),
  angle_(0.0)
{
  if (r < 0.0)
  {
    throw std::invalid_argument("Invalid radius_ !");
  }
  radius_ = r;
}

double mihajlov::Circle::getArea() const
{
  return (M_PI * radius_ * radius_);
}

mihajlov::rectangle_t mihajlov::Circle::getFrameRect() const
{
  return rectangle_t{pos_, 2 * radius_, 2 * radius_};
}

void mihajlov::Circle::move(const point_t& centerPos)
{
  pos_.x = centerPos.x;
  pos_.y = centerPos.y;
}

void mihajlov::Circle::move(const double shiftX, const double shiftY)
{
  pos_.x += shiftX;
  pos_.y += shiftY;
}

void mihajlov::Circle::getInfo() const
{
  std::cout << "Current Circle data_: " << std::endl;
  std::cout << "X = " << pos_.x << "; Y = " << pos_.y << ";" << std::endl;
  std::cout << "Radius = " << radius_ << ";" << std::endl;
}

void mihajlov::Circle::printName() const
{
  std::cout << "Circle ";
}

void mihajlov::Circle::scale(const double multiplier)
{
  if (multiplier < 0.0)
  {
    throw std::invalid_argument("Invalid multiplier!");
  }
  radius_ *= multiplier;
}

void mihajlov::Circle::rotate(const double angle)
{
  angle_ += angle;
}
