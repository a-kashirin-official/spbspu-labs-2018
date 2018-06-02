#include "triangle.hpp"
#include <iostream>
#include <algorithm>

Triangle::Triangle(const point_t &a, const point_t &b, const point_t &c) :
  A_(a),
  B_(b),
  C_(c)
{
  if (getArea() <= 0)
  {
    std::cerr << "Wrong coordinates of vertices of a triangle." << std::endl;
  }
  pos_.x = (A_.x + B_.x + C_.x) / 3;
  pos_.y = (A_.y + B_.y + C_.y) / 3;
}

double Triangle::getArea() const
{
  return ( (A_.x - C_.x)*(B_.y - C_.y) - (B_.x - C_.x)*(A_.y - C_.y) ) / 2;
}

rectangle_t Triangle::getFrameRect() const
{
  double minX = std::min(std::min(A_.x, B_.x), C_.x);

  double maxX = std::max(std::max(A_.x, B_.x), C_.x);

  double minY = std::min(std::min(A_.y, B_.y), C_.y);

  double maxY = std::max(std::max(A_.y, B_.y), C_.y);

  return { maxX - minX , maxY - minY , { (maxX - minX) / 2 , (maxY - minY) / 2 } };
}

void Triangle::showSize() const
{
  std::cout << "Coordinates of vertices of a triangle: ";
  std::cout << "A(" << A_.x << ";" << A_.y << "), ";
  std::cout << "B(" << B_.x << ";" << B_.y << "), ";
  std::cout << "C(" << B_.x << ";" << C_.y << "). " << std::endl;
}

void Triangle::showPos() const
{
  std::cout << "Coordinates of the center of the triangle: ";
  std::cout << "X = " << pos_.x << " Y = " << pos_.y << std::endl;
}

void Triangle::move(const point_t &pos)
{
  A_.x += pos.x - pos_.x;

  B_.y += pos.y - pos_.y;

  B_.x += pos.x - pos_.x;

  B_.y += pos.y - pos_.y;

  C_.x += pos.x - pos_.x;

  C_.y += pos.y - pos_.y;

  pos_ = pos;

}

void Triangle::move(const double dx, const double dy)
{

  A_.x += dx;

  A_.y += dy;

  B_.x += dx;

  B_.y += dy;

  C_.x += dx;

  C_.y += dy;

  pos_.x += dx;
  pos_.y += dy;

}

