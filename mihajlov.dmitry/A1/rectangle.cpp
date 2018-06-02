#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const point_t & centerPos, const double height, const double width):
  data{{centerPos.x, centerPos.y}, 0.0, 0.0}
{
  if ((height < 0.0) || (width < 0.0))
  {
    throw std::invalid_argument("Invalid height/width !");
  }
  data.height = height;
  data.width = width;
}

Rectangle::Rectangle(const rectangle_t & tempRect):
  data{{tempRect.pos.x, tempRect.pos.y}, tempRect.height, tempRect.width}
{
  if ((tempRect.height < 0.0) || (tempRect.width < 0.0))
  {
    std::cerr << "An error! Height and width must be positive!" << std::endl;
  }
}

double Rectangle::getArea() const
{
  return (this->data.height)*(this->data.width);
}

rectangle_t Rectangle::getFrameRect() const
{
  return (this->data);
}

void Rectangle::move(const point_t & centerPos)
{
  this->data.pos.x = centerPos.x;
  this->data.pos.y = centerPos.y;
}

void Rectangle::move(const double shiftX, const double shiftY)
{
  this->data.pos.x += shiftX;
  this->data.pos.y += shiftY;
}

void Rectangle::getInfo() const
{
  std::cout << "Current Rectangle data: " << std::endl;
  std::cout << "X = " << this->data.pos.x << "; Y = " << this->data.pos.y << ";" << std::endl;
  std::cout << "Height = " << this->data.height << "; Width = " << this->data.width <<  ";" << std::endl;
}
