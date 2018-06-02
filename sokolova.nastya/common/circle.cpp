#include "circle.hpp"

#include <iostream>
#include <cmath>
#include <stdexcept>

sokolova::Circle::Circle(const sokolova::point_t &centre, double radius) :
  radius_(radius),
  angle_(0.0)
{
  centre_ = centre;
  if (radius_ < 0.0) {
    throw std::invalid_argument("Wrong radius!");
  }
}

double sokolova::Circle::getArea() const noexcept
{
  return M_PI * radius_ * radius_;
}

sokolova::rectangle_t sokolova::Circle::getFrameRect() const noexcept
{
  return {centre_, 2 * radius_, 2 * radius_ };
}

void sokolova::Circle::move(const double dx, const double dy) noexcept
{
  centre_.x += dx;
  centre_.y += dy;
}

void sokolova::Circle::move(const sokolova::point_t &newcentre) noexcept
{
  centre_ = newcentre;
}

void sokolova::Circle::scale(const double factor)
{
  if (factor < 0.0) {
    throw std::invalid_argument("Wrong factor!");
  }
  radius_ *= factor;
}

void sokolova::Circle::rotate(const double) noexcept
{
}

std::unique_ptr<sokolova::Shape> sokolova::Circle::getCopy() const noexcept
{
  return std::unique_ptr<sokolova::Shape>(new Circle(*this));
}

void sokolova::Circle::printInfo() const
{
  std::cout << "Circle" << std::endl;
  std::cout << "Area: " << getArea() << std::endl;
  const sokolova::rectangle_t frame = getFrameRect();
  std::cout << "Frame for object:" << std::endl;
  std::cout << "Centre: " << frame.pos.x << ", " << frame.pos.y << std::endl;
  std::cout << "Radius: " << frame.width/2.0 << std::endl;
}
