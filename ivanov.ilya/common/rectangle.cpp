#include "rectangle.hpp"
#include <stdexcept>
#include <iostream>

ivanov::Rectangle::Rectangle(const rectangle_t & rect):
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

void ivanov::Rectangle::show() const
{
  std::cout << "Object of rectangle: " << "\n";
  std::cout << "Area = " << getArea() << "\n";
  rectangle_t border = getFrameRect();
  std::cout << "X coord: " << border.pos.x << ", Y coord: " << border.pos.y;
  std::cout << ", width = " << border.width << ", height = " <<border.height << "\n";
}

double ivanov::Rectangle::getArea() const
{
  return bar_.width * bar_.height;
}

ivanov::rectangle_t ivanov::Rectangle::getFrameRect() const
{
  return bar_;
}

void ivanov::Rectangle::move(const point_t & point)
{
  bar_.pos = point;
}

void ivanov::Rectangle::move(double dx, double dy)
{
  bar_.pos.x += dx;
  bar_.pos.y += dy;
}

void ivanov::Rectangle::scale(double koeff)
{
  if (koeff < 0.0)
  {
    throw std::invalid_argument("Koefficient must be positive or equal zero");
  }
  bar_.width *= koeff;
  bar_.height *= koeff;
}
