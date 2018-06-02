#include "rectangle.hpp"
#include <stdexcept>

gusev::Rectangle::Rectangle(const double width,const double height, const point_t &pos):
  width_(width),
  height_(height),
  center_(pos)
{
  if (width <= 0 || height <= 0)
  {
    throw std::invalid_argument("Invalid argument");
  }
}

double gusev::Rectangle::getArea() const
{
  return width_ * height_;
}

gusev::rectangle_t gusev::Rectangle::getFrameRect() const
{
  return {width_, height_, center_};
}

gusev::point_t gusev::Rectangle::getCenter() const
{
  return center_;
}

void gusev::Rectangle::move(const point_t &newPoint)
{
  center_ = newPoint;
}

void gusev::Rectangle::move(const double dx,const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void gusev::Rectangle::scale(const double coef)
{
  if (coef <= 0)
  {
    throw std::invalid_argument("Invalid coef");
  }
  width_ *= coef;
  height_ *= coef;
}
