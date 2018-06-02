#include "circle.hpp"
#include <iostream>
#include <cmath>

Circle::Circle(const point_t & centerPos, const double r):
  pos{centerPos.x, centerPos.y},
  radius(0.0)
{
  if (r < 0.0)
  {
    throw std::invalid_argument("Invalid radius !");
  }
  radius = r;
}

double Circle::getArea() const
{
  return M_PI*(this->radius)*(this->radius);
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{this->pos, 2*(this->radius), 2*(this->radius)};
}

void Circle::move(const point_t &centerPos)
{
  this->pos.x = centerPos.x;
  this->pos.y = centerPos.y;
}

void Circle::move(const double shiftX, const double shiftY)
{
  this->pos.x += shiftX;
  this->pos.y += shiftY;
}

void Circle::getInfo() const
{
  std::cout << "Current Circle data: " << std::endl;
  std::cout << "X = " << this->pos.x << "; Y = " << this->pos.y << ";" << std::endl;
  std::cout << "Radius = " << this->radius << ";" << std::endl;
}
