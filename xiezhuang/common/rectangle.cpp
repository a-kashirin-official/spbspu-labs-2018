#include <iostream>
#include <stdexcept>
#include <cmath>
#include "rectangle.hpp"

using namespace xiezhuang;

Rectangle::Rectangle(const point_t &pos, double width, double height):
  pos_(pos),
  width_(width),
  height_(height)
{
  if (width < 0.0)
  {
    throw std::invalid_argument("invalid width");
  }

  if (height < 0.0)
  {
    throw std::invalid_argument("invalid height");
  }
}

point_t Rectangle::getPosition() const
{
  return pos_;
}

double Rectangle::getWidth() const
{
  return width_;
}

double Rectangle::getHeight() const
{
  return height_;
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

void Rectangle::scale(double factor)
{
  if (factor <= 0.0)
  {
    throw std::invalid_argument("invalid scaling factor");
  }

  width_ *= factor;
  height_ *= factor;
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
  std::cout << "center = (" << pos_.x << ", " << pos_.y << ")" << std::endl
    << "height = " << height_ << " width = " << width_ << std::endl;
}
