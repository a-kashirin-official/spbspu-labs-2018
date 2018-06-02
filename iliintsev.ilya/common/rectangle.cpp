#include "rectangle.hpp"
#include <stdexcept>

using namespace iliintsev;

Rectangle::Rectangle(const point_t & center, double width, double height) :
  center_(center),
  width_(width),
  height_(height)
{
  if (height_ < 0.0)
  {
    throw std::invalid_argument(" error, height can't be < 0 ");
  }

  if (width_ < 0.0)
  {
    throw std::invalid_argument(" error, weigth can't be < 0 ");
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return{center_, width_, height_};
}

void Rectangle::move(const point_t & new_center)
{
  center_ = new_center;
}

void Rectangle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Rectangle::scale(const double koef)
{
  if (koef < 0.0)
  {
    throw std::invalid_argument(" error, koef can't be < 0 ");
  }

  width_ *= koef;
  height_ *= koef;
}

point_t Rectangle::getCenter() const
{
  return center_;
}
