#include "rectangle.hpp"
#include <iostream>
#include <stdexcept>

using namespace turgunov;

Rectangle::Rectangle(const point_t &pos, double width, double height):
  pos_(pos),
  width_(width),
  height_(height)
{
  if (width < 0)
  {
    throw std::invalid_argument("invalid width");
  }

  if (height < 0)
  {
    throw std::invalid_argument("invalid height");
  }
}

double Rectangle::getWidth() const
{
  return width_;
}

double Rectangle::getHeight() const
{
  return height_;
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {pos_, width_, height_};
}

void Rectangle::printInfo() const
{
 
  std::cout << "x: " << pos_.x << "\n"
    << "y: " << pos_.y << "\n"
    << "width: " << width_ << "\n"
    << "height: " << height_ << "\n";
}

void Rectangle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void Rectangle::move(const point_t &pos)
{
  pos_ = pos;
}

void Rectangle::scale(double k)
{
  if (k <= 0)
  {
    throw std::invalid_argument("invalid scaling factor");
  }

  width_ *= k;
  height_ *= k;
}
