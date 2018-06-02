#include "rectangle.hpp"
#include <iostream>

kostylev::Rectangle::Rectangle(const point_t & centre, const double width, const double height):
  centre_(centre),
  width_(width),
  height_(height)
{
  if ((height < 0.0) || (width < 0.0))
  {
    throw std::invalid_argument("Error. Invalid height or width of rectangle.");
  }
}

double kostylev::Rectangle::getArea() const
{
  return width_ * height_;
}

kostylev::rectangle_t kostylev::Rectangle::getFrameRect() const
{
  return {centre_, width_, height_};
}

void kostylev::Rectangle::move(const point_t & point)
{
  centre_ = point;
}

void kostylev::Rectangle::move(const double dx, const double dy)
{
  centre_.x += dx;
  centre_.y += dy;
}

void kostylev::Rectangle::scale(const double coef)
{
  if (coef < 0.0)
  {
    throw std::invalid_argument("Error. Invalid parameter of scaling.");
  }
  width_ *= coef;
  height_ *= coef;
}
