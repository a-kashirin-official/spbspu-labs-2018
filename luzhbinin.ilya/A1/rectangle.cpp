#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const rectangle_t & rectan) :
  rectan_(rectan)
{
  if (rectan.height < 0.0)
  {
    std::cerr << "Invalid_rectangle_height" << std::endl;
  }
  if (rectan.width < 0.0)
  {
    std::cerr << "Invalid_rectangle_width" << std::endl;
  }
}

double Rectangle::getArea() const
{
  return rectan_.height * rectan_.width;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rectan_;
}

void Rectangle::move(const point_t & to)
{
  rectan_.pos = to;
}

void Rectangle::move(double dx, double dy)
{
  rectan_.pos.x += dx;
  rectan_.pos.y += dy;
}
