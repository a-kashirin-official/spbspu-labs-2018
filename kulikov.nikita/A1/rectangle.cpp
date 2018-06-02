#include "rectangle.hpp"
#include <stdexcept>
#include <iostream>

Rectangle::Rectangle(const rectangle_t & rect):
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

void Rectangle::show() const
{
  std::cout << "Object of rectangle: " << "\n";
  std::cout << "Area = " << getArea() << "\n";
  rectangle_t border = getFrameRect();
  std::cout << "X coord: " << border.pos.x << ", Y coord: " << border.pos.y;
  std::cout << ", width = " << border.width << ", height = " <<border.height << "\n";
}

double Rectangle::getArea() const
{
  return bar_.width * bar_.height;
}

rectangle_t Rectangle::getFrameRect() const
{
  return bar_;
}

void Rectangle::move(const point_t & p)
{
  bar_.pos = p;
}

void Rectangle::move(double dx, double dy)
{
  bar_.pos.x += dx;
  bar_.pos.y += dy;
}
