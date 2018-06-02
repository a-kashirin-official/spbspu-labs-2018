#include "rectangle.hpp"

#include <stdexcept>

Rectangle::Rectangle(const point_t & pos, const double width, const double height):
  pos_(pos),
  width_(width),
  height_(height)
{
  if (width < 0.0)
  {
    throw std::invalid_argument("Rectangle: Width value must be non-negative");
  }
  if (height < 0.0)
  {
    throw std::invalid_argument("Rectangle: Height value must be non-negative");
  }
}

void Rectangle::setWidth(const double width)
{
  if (width < 0.0)
  {
    throw std::invalid_argument("Rectangle: Width value must be non-negative");
  }

  width_ = width;
}

double Rectangle::getWidth() const
{
  return width_;
}

void Rectangle::setHeight(const double height)
{
  if (height < 0.0)
  {
    throw std::invalid_argument("Rectangle: Height value must be non-negative");
  }

  height_ = height;
}

double Rectangle::getHeight() const
{
  return height_;
}

point_t Rectangle::getPos() const
{
  return pos_;
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return { pos_, width_, height_ };
}

void Rectangle::move(const point_t & pos)
{
  pos_ = pos;
}

void Rectangle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}
