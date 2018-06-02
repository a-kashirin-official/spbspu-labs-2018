#include "triangle.hpp"

#include <iostream>
#include <cmath>

zabrodina::Triangle::Triangle(const point_t &point1, const point_t &point2, const point_t &point3):
  A_(point1),
  B_(point2),
  C_(point3)
{
 if(getArea() <= 0)
  {
    throw std::invalid_argument("Error: wrong parametres");
  }
}

double zabrodina::Triangle::getLength(const point_t &p1, const point_t &p2)
{
  return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}

double zabrodina::Triangle::getArea() const
{
  double ab = getLength(A_, B_);
  double bc = getLength(B_, C_);
  double ca = getLength(C_, A_);
  double p = (ab + ca + bc) / 2;
  return std::sqrt(p*(p - ab)*(p - bc)*(p - ca));
}

zabrodina::rectangle_t zabrodina::Triangle::getFrameRect() const
{
  double left = std::min(std::min(A_.x, B_.x), C_.x);
  double bottom = std::min(std::min(A_.y, B_.y), C_.y);
  double top = (std::max(std::max(A_.y, B_.y), C_.y));
  double right = (std::max(std::max(A_.x, B_.x), C_.x)) ;
  return {right - left, top - bottom, (right + left)/2, (top + bottom)/2};
}

void zabrodina::Triangle::move(double Ox, double Oy)
{
  A_.x += Ox;
  B_.x += Ox;
  C_.x += Ox;
  A_.y += Oy;
  B_.y += Oy;
  C_.y += Oy;
}

void zabrodina::Triangle::move(const point_t &p)
{
  move(p.x - findCenter().x, p.y - findCenter().y);
}

zabrodina::point_t zabrodina::Triangle::findCenter() const
{
  return point_t{ (A_.x + B_.x + C_.x) / 3, (A_.y + B_.y + C_.y) / 3 };
}

void zabrodina::Triangle::printInf() const
{
  std::cout << "Area of a triangle: " << Triangle::getArea() << std::endl;
  point_t center = findCenter();
  std::cout << "Center of a triangle: " << "(" << center.x << "," << center.y << ")" << std::endl;
  rectangle_t frame = getFrameRect();
  std::cout << "Frame Center ("<< frame.pos.x << "," << frame.pos.y << ")" << std::endl;
  std::cout << "Frame Width: " << frame.width << "   Frame Height: " << frame.height << std::endl;
}

void zabrodina::Triangle::scale(const double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Error: coefficient <= 0");
  }
  else
  {
    point_t center = findCenter();
    A_.x = center.x + (A_.x - center.x) * coefficient;
    A_.y = center.y + (A_.y - center.y) * coefficient;
    B_.x = center.x + (B_.x - center.x) * coefficient;
    B_.y = center.y + (B_.y - center.y) * coefficient;
    C_.x = center.x + (C_.x - center.x) * coefficient;
    C_.y = center.y + (C_.y - center.y) * coefficient;
  }
}
