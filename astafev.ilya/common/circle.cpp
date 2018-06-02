
#include "circle.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>

astafev::Circle::Circle(const point_t &centre, double radius) :
  centre_(centre),
  radius_(radius)
{
    if (radius_ < 0.0)
  {
    throw std::invalid_argument("err, radius can`t be < 0 ");
  }
}

double astafev::Circle::getArea() const noexcept
{
  return M_PI*radius_*radius_;
}

astafev::rectangle_t astafev::Circle::getFrameRect() const noexcept
{
  return {centre_, 2 * radius_, 2 * radius_};
}

void astafev::Circle::scale(double koeficent)
{
  if (koeficent <= 0.0) 
  {
    throw std::invalid_argument("error, koeficent can't be <=0 ");
  }
  radius_ *= koeficent;
}

void astafev::Circle::move(const double dx, const double dy) noexcept
{
  centre_.x += dx;
  centre_.y += dy;
}

void astafev::Circle::move(const point_t &newcentre) noexcept
{
  centre_ = newcentre;
}

void astafev::Circle::rotate(const double /*degrees*/) noexcept
{
}

void astafev::Circle::printInfo() const noexcept
{
  std::cout << "Circle:  " << "  Radius - " << radius_ << ";"<<std::endl;
  std::cout << "  Center - " << "x = " << centre_.x << ", y = " << centre_.y << ";"<<std::endl;
}

size_t astafev::Circle::getSize() const noexcept
{
  return 1;
}
