#include "rectangle.hpp"

#include <stdexcept>

pichugina::Rectangle::Rectangle(const pichugina::point_t & middle, const double width, const double height):
  middle_(middle),
  width_(width),
  height_(height)
  {
  if (width < 0.0)
  {
    throw std::invalid_argument("Invalid rectangle width");
  }
  if (height < 0.0)
  {
    throw std::invalid_argument("Invalid rectangle height");
  }
}

double pichugina::Rectangle::getArea() const
{
  return width_ * height_;
}

pichugina::rectangle_t pichugina::Rectangle::getFrameRect() const
{
  return {middle_, width_, height_};
}

void pichugina::Rectangle::move(const pichugina::point_t & pos)
{
  middle_ = pos;
}

void pichugina::Rectangle::move(const double dx, const double dy)
{
  middle_.x += dx;
  middle_.y += dy;
}

void pichugina::Rectangle::scale(const double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Invalid factor");
  }
  width_ *= factor;
  height_ *= factor;
}
