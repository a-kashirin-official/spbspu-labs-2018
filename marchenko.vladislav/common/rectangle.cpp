#include "rectangle.hpp"
#include <iostream>
#include <stdexcept>

marchenko::Rectangle::Rectangle(const double width, const double height, const point_t &centerPos) :
  width_(width),
  height_(height),
  center_(centerPos)
{
  if (width_ < 0.0)
  {
    throw std::invalid_argument("Invalid value of width. It must be >=0.");
  }
  if (height_ < 0.0)
  {
    throw std::invalid_argument("Invalid value of height. It must be >=0.");
  }
}

double marchenko::Rectangle::getArea() const
{
  return width_ * height_;
}

marchenko::rectangle_t marchenko::Rectangle::getFrameRect() const
{
  return { width_ , height_ , center_ };
}

void marchenko::Rectangle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void marchenko::Rectangle::move(const point_t &newPos)
{
  center_ = newPos;
}

void marchenko::Rectangle::scale(const double coefficient)
{
  if (coefficient < 0.0)
  {
    throw std::invalid_argument("Invalid coefficient of scale. It must be >=0.");
  }
  else
  {
    width_ *= coefficient;
    height_ *= coefficient;
  }
}

