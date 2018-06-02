#include "rectangle.hpp"
#include <stdexcept>
#include <iostream>

kulikov::Rectangle::Rectangle(const rectangle_t & rect):
  bar_(rect)
{
  if(rect.width < 0.0)
  {
    throw std::invalid_argument("Rectangle negative width");
  }
  if (rect.height < 0.0)
  {
    throw std::invalid_argument("Rectangle negative height");
  }
}

double kulikov::Rectangle::getArea() const
{
  return bar_.width * bar_.height;
}

kulikov::rectangle_t kulikov::Rectangle::getFrameRect() const
{
  return bar_;
}

void kulikov::Rectangle::move(const point_t & point)
{
  bar_.pos = point;
}

void kulikov::Rectangle::move(double dx, double dy)
{
  bar_.pos.x += dx;
  bar_.pos.y += dy;
}

void kulikov::Rectangle::scale(double koeff)
{
  if (koeff < 0.0)
  {
    throw std::invalid_argument("Koefficient must be positive or equal zero");
  }
  bar_.width *= koeff;
  bar_.height *= koeff;
}
