#include "rectangle.hpp"
#include <iostream>
using namespace reznikov;

Rectangle::Rectangle(double width, double height, const point_t &center) :
  width_(width),
  height_(height),
  center_(center)
{
  if ((width_ < 0.0) || (height_ < 0.0))
  {
    throw std::invalid_argument("Invalid rectangle height or width.They must be above zero");
  }
}

rectangle_t Rectangle::getFrameRect() const
{
  return { width_, height_, center_ };
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

void Rectangle::move(const point_t &point)
{
  center_ = point;
}

void Rectangle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Rectangle::inf() const
{
  std::cout << "Rectangle:" << std::endl;
  std::cout << "Width: " << width_ << std::endl;
  std::cout << "  Height: " << height_ << std::endl;
  std::cout << "  Position:  " << " x: " << center_.x << "   y: " << center_.y << std::endl;
  std::cout << "  Area: " << this->getArea() << std::endl;
}

void Rectangle::scale(const double coefficient)
{
  if (coefficient < 0.0)
  {
    throw std::invalid_argument("Invalid scale coefficient. Scale coefficient must be above zero.");
  }
  else
  {
    width_ *= coefficient;
    height_ *= coefficient;
  }
}

point_t Rectangle::getPosition() const 
{
  return getFrameRect().pos;
}


