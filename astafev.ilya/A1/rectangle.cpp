#include "rectangle.hpp"
#include <stdexcept>

Rectangle::Rectangle(const point_t &centre, double width, double height) :
  centre_(centre),
  width_(width),
  height_(height)
{
  if (height_ < 0.0)
  {
    height_ = 0.0;
    std::invalid_argument("error, height can't be <0 ");
  }
  if (width_ < 0.0)
  {
    width_ = 0.0;
    std::invalid_argument("error, widht can't be <0 ");
  }
}

double Rectangle::getArea() const noexcept
{
  return width_*height_;
}

rectangle_t Rectangle::getFrameRect() const noexcept
{
  return {centre_, width_, height_};
}

void Rectangle::move(const double dx, const double dy) noexcept
{
  centre_.x += dx;
  centre_.y += dy;
}

void Rectangle::move(const point_t &newcentre) noexcept
{
  centre_ = newcentre;
}

