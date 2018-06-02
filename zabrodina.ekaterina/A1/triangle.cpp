#include "triangle.hpp"

#include <iostream>
#include <cmath>

Triangle::Triangle(const point_t &point1, const point_t &point2, const point_t &point3):
  A_(point1),
  B_(point2),
  C_(point3)
{
  if(getArea() <= 0)
  {
    throw std::invalid_argument("Error: wrong parametres");
  }
}

double Triangle::getLength(const point_t &p1, const point_t &p2)
{
  return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}

double Triangle::getArea() const
{
  double ab = getLength(A_, B_);
  double bc = getLength(B_, C_);
  double ca = getLength(C_, A_);
  double p = (ab + ca + bc) / 2;
  return std::sqrt(p*(p - ab)*(p - bc)*(p - ca));
}

rectangle_t Triangle::getFrameRect() const
{
  double left = std::min(std::min(A_.x, B_.x), C_.x);
  double bottom = std::min(std::min(A_.y, B_.y), C_.y);
  double h = (std::max(std::max(A_.y, B_.y), C_.y));
  double w = (std::max(std::max(A_.x, B_.x), C_.x)) ;
  return {w - left, h - bottom, (w + left)/2, (h + bottom)/2};
}

void Triangle::move(double Ox, double Oy)
{
  A_.x += Ox;
  B_.x += Ox;
  C_.x += Ox;
  A_.y += Oy;
  B_.y += Oy;
  C_.y += Oy;
}

void Triangle::move(const point_t &p)
{
  move(p.x - findCenter().x, p.y - findCenter().y);
}

point_t Triangle::findCenter() const
{
  return point_t{ (A_.x + B_.x + C_.x) / 3, (A_.y + B_.y + C_.y) / 3 };
}

void Triangle::printInf()
{
  std::cout << "Area of a triangle: " << Triangle::getArea() << std::endl;
  point_t center = findCenter();
  std::cout << "Center of a triangle: " << "(" << center.x << "," << center.y << ")" << std::endl;
  rectangle_t frame = getFrameRect();
  std::cout << "Frame Center (" << frame.pos.x << "," << frame.pos.y << ")" << std::endl;
  std::cout << "Frame Width: " << frame.width << "   Frame Height: " << frame.height << std::endl;
}


