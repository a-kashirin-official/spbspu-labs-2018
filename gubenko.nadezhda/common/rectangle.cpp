#include "rectangle.hpp"
#include <stdexcept>
#include <cassert>

using namespace gubenko;

Rectangle::Rectangle(const point_t & pos, double width, double height):
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

void Rectangle::move(const point_t & pos)
{
  pos_ = pos;
}

void Rectangle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void Rectangle::scale(double n)
{
  if (n < 0.0)
  {
    throw std::invalid_argument("n must be >= 0");
  }
  width_ *= n;
  height_ *= n;
}

std::ostream & gubenko::operator <<(std::ostream & out, const Rectangle & r)
{
  out << "Area: " << r.getArea() << std::endl;
  out <<"pos (" << r.getFrameRect().pos.x << ", " << r.getFrameRect().pos.y << ")" << std::endl;
  out << "width: " << r.getFrameRect().width << std::endl;
  out << "height: " << r.getFrameRect().height;

  return out;
}
