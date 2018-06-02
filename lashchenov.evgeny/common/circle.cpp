#include "circle.hpp"
#include <cmath>
#include <iostream>

using namespace lashchenov;

Circle::Circle(const double radius, const point_t & center) :
  radius_(radius),
  center_(center)
{
  if ((radius_ < 0)) {
    throw std::invalid_argument("Circle radius can't be < 0");
  }
}

Circle::Circle(const double radius, const double x, const double y) :
  radius_(radius)
{
  center_.x = x;
  center_.y = y;
  if ((radius_ < 0)) {
    throw std::invalid_argument("Circle radius can't be < 0");
  }
}

double Circle::getArea() const
{
  return radius_ * radius_ * M_PI;
}

rectangle_t Circle::getFrameRect() const
{
  return {radius_ * 2, radius_ * 2, {center_.x, center_.y}};
}

void Circle::move(const point_t & NewCenter)
{
  center_ = NewCenter;
}

void Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Circle::scale(const double multiplier)
{
  if (multiplier < 0) {
    throw std::invalid_argument("Scale multiplier for circle can't be < 0");
  }
  radius_ *= multiplier;
}

void Circle::rotate(double /*degrees*/)
{
}

std::unique_ptr<Shape> Circle::getCopy() const
{
  return std::unique_ptr<Shape>(new Circle(*this));
}

void Circle::printInfo() const
{
  std::cout << "Circle:  ";
  std::cout << "  Radius - " << radius_ << ";";
  std::cout << "  Center - ";
  std::cout << "x = " << center_.x << ", y = " << center_.y << ";";
  std::cout << "  Area: " << getArea() << std::endl;
}
