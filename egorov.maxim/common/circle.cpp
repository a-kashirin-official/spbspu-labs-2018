#include "circle.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace egorov;

Circle::Circle(const double radius, const point_t &centr) :
  radius_(radius), centr_(centr)
{
  if (radius_ < 0.0)
  {
    throw std::invalid_argument("invalid_radius");
  }
}

double Circle::getArea() const noexcept
{
  return radius_ * radius_ * M_PI;
}

rectangle_t Circle::getFrameRect() const noexcept
{
  return rectangle_t{(radius_ * 2), (radius_ * 2), centr_ };
}

void Circle::move(const point_t &point) noexcept
{
  centr_ = point;
}

void Circle::move(const double deltaX, const double deltaY) noexcept
{
  centr_.x += deltaX;
  centr_.y += deltaY;
}

void Circle::scale(const double coefficent)
{
  if (coefficent < 0.0)
  {
    throw std::invalid_argument("invalid_coefficent");
  }
  radius_ *= coefficent;
}

void Circle::rotate(double) noexcept
{
}

std::string Circle::getName() const  noexcept
{
  return "Circle";
}
