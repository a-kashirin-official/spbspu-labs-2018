#include "circle.hpp"

#include <iostream>
#include <cmath>
#include <stdexcept>

strashko::Circle::Circle(const strashko::point_t &centre, double radius) :
  radius_(radius),
  angle_(0.0)
{
  centre_ = centre;
  if (radius_ < 0.0) {
    throw std::invalid_argument("Wrong radius!");
  }
}

double strashko::Circle::getArea() const noexcept
{
  return M_PI * radius_ * radius_;
}

strashko::rectangle_t strashko::Circle::getFrameRect() const noexcept
{
  return {centre_, 2 * radius_, 2 * radius_ };
}

void strashko::Circle::move(const double dx, const double dy) noexcept
{
  centre_.x += dx;
  centre_.y += dy;
}

void strashko::Circle::move(const strashko::point_t &newcentre) noexcept
{
  centre_ = newcentre;
}

void strashko::Circle::scale(const double factor)
{
  if (factor < 0.0) {
    throw std::invalid_argument("Wrong factor!");
  }
  radius_ *= factor;
}

void strashko::Circle::rotate(const double) noexcept
{
}

std::unique_ptr<strashko::Shape> strashko::Circle::getCopy() const noexcept
{
  return std::unique_ptr<strashko::Shape>(new Circle(*this));
}

void strashko::Circle::printInfo() const
{
  std::cout << "Circle:  ";
  std::cout << "  Radius - " << radius_ << ";";
  std::cout << "  Center - ";
  std::cout << "x = " << centre_.x << ", y = " << centre_.y << ";";
  std::cout << "  Area: " << getArea() << std::endl;
}
