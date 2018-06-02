#include "triangle.hpp"
#include <array>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

using namespace gerastyonok;

gerastyonok::Triangle::Triangle(const point_t & a, const point_t & b, const point_t & c) : 
  a_(a),
  b_(b),
  c_(c)
{
  center_.x = (a_.x + b_.x + c_.x) / 3;
  center_.y = (a_.y + b_.y + c_.y) / 3;
}

double gerastyonok::Triangle::getArea() const
{
  return ((a_.x - c_.x)* (b_.y - c_.y) - (b_.x - c_.x) * (a_.y - c_.y)) / 2;
}

rectangle_t gerastyonok::Triangle::getFrameRect() const
{
  double minX(std::min(std::min(a_.x, b_.x), c_.x));
  double maxX(std::max(std::max(a_.x, b_.x), c_.x));
  double minY(std::min(std::min(a_.y, b_.y), c_.y));
  double maxY(std::max(std::max(a_.y, b_.y), c_.y));
  return rectangle_t {maxY - minY , maxX - minX , { (minX + maxX) / 2 , (minY + maxY) / 2 } };
}

void gerastyonok::Triangle::move(const point_t & pos)
{
  a_.x += pos.x - center_.x;
  a_.y += pos.y - center_.y;
  b_.x += pos.x - center_.x;
  b_.y += pos.y - center_.y;
  c_.x += pos.x - center_.x;
  c_.y += pos.y - center_.y;
  center_ = pos;
}

void gerastyonok::Triangle::move(double px, double py)
{
  a_.x += px;
  a_.y += py;
  b_.x += px;
  b_.y += py;
  c_.x += px;
  c_.y += py;
  center_.x += px;
  center_.y += py;
}

void gerastyonok::Triangle::scale(const double k)

{
  
  if (k < 0.0)
  {
   
    throw std::invalid_argument("Error!");

  }
 
  a_ = {center_.x + k * (a_.x - center_.x), center_.y + k * (a_.y - center_.y)};
 
  b_ = {center_.x + k * (b_.x - center_.x), center_.y + k * (b_.y - center_.y)};
  
  c_ = {center_.x + k * (c_.x - center_.x), center_.y + k * (c_.y - center_.y)};

}


point_t gerastyonok::Triangle::getCenter() const
{
  return center_;
}
