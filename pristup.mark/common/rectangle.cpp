#include <iostream>

#include "rectangle.hpp"

pristup::Rectangle::Rectangle(const rectangle_t & rect):
  rect_(rect)
{
  if ((rect_.height < 0.0) || (rect_.width < 0.0))
  {
    throw std::invalid_argument("it is not right height or width of rectangle");
  }
}

double pristup::Rectangle::getArea() const noexcept
{
  return (rect_.width * rect_.height);
}

pristup::rectangle_t pristup::Rectangle::getFrameRect() const noexcept
{
  return rect_;
}


void pristup::Rectangle::move(const point_t & p) noexcept
{
  rect_.pos = p;
}

void pristup::Rectangle::move(double dx, double dy) noexcept
{
  rect_.pos.x += dx;
  rect_.pos.y += dy;
}

void pristup::Rectangle::scale(double k)
{
    if (k < 0.0)
    {
        throw std::invalid_argument("it is not right parameter of scaling");
    }
    rect_.width *= k;
    rect_.height *= k;
}

