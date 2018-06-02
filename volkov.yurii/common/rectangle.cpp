#include "rectangle.hpp"
#include <stdexcept>
#include <cassert>

using namespace volkov;

Rectangle::Rectangle(const point_t & pos, double width, double height):
  pos_(pos),
  width_(width),
  height_(height)
{
  if (width < 0.0)
  {
    throw std::invalid_argument("erroneus width");
  }

  if (height < 0.0)
  {
    throw std::invalid_argument("erroneus height");
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

void Rectangle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void Rectangle::scale(const double f)
{
  if (f < 0.0)
  {
    throw std::invalid_argument("f be sure >= 0");
  }
  width_ *= f;
  height_ *= f;
}

std::ostream & volkov::operator <<(std::ostream & out, const Rectangle & rect)
{
  out << "Area: " << rect.getArea() << std::endl;
  out <<"pos (" << rect.getFrameRect().pos.x << ", " << rect.getFrameRect().pos.y << ")" << std::endl;
  out << "width: " << rect.getFrameRect().width << std::endl;
  out << "height: " << rect.getFrameRect().height;

  return out;
}
