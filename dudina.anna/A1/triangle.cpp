#include "triangle.hpp"
#include <cmath>
#include <algorithm>


Triangle::Triangle(const point_t & A, const point_t & B, const point_t & C) :
  A_(A),
  B_(B),
  C_(C)
{
  centerpos_ = { (A_.x + B_.x + C_.x) / 3, (A_.y + B_.y + C_.y) / 3 };
  if (getArea() <= 0)
  {
    std::cerr << "Wrong coordinates" << std::endl;
  }
 }

double Triangle::getArea() const
{
  double ab = sqrt((A_.x - B_.x)*(A_.x - B_.x) + (A_.y - B_.y)*(A_.y - B_.y));
  double bc = sqrt((B_.x - C_.x)*(B_.x - C_.x) + (B_.y - C_.y)*(B_.y - C_.y));
  double ca = sqrt((C_.x - A_.x)*(C_.x - A_.x) + (C_.y - A_.y)*(C_.y - A_.y));
  double p = (ab + bc + ca)/2.0;
  return std::sqrt(p*(p - ab)*(p - bc)*(p - ca));
}

rectangle_t Triangle::getFrameRect() const
{
  double maxX = std::max(std::max(A_.x, B_.x), C_.x);
  double minX = std::min(std::min(A_.x, B_.x), C_.x);
  double maxY = std::max(std::max(A_.y, B_.y), C_.y);
  double minY = std::min(std::min(A_.y, B_.y), C_.y);
  return { maxX - minX, maxY - minY,{ (maxX + minX) / 2.0,(maxY + minY) / 2.0 }};
}

void Triangle::move(const point_t & pos)
{
  A_.x += pos.x - centerpos_.x;
  A_.y += pos.y - centerpos_.y;
  B_.x += pos.x - centerpos_.x;
  B_.y += pos.y - centerpos_.y;
  C_.x += pos.x - centerpos_.x;
  C_.y += pos.y - centerpos_.y;
  centerpos_.x = pos.x;
  centerpos_.y = pos.y;
}

void Triangle::move(const double dx, const double dy)
{
  centerpos_.x += dx;
  A_.x += dx;
  B_.x += dx;
  C_.x += dx;
  centerpos_.y += dy;
  A_.y += dy;
  B_.y += dy;
  C_.y += dy;
}


void Triangle::printInformation()
{
  std::cout << "Triangle" << std::endl;
  std::cout << "Coordinates of vertex A: {" << A_.x << "," << A_.y << "}" << std::endl;
  std::cout << "Coordinates of vertex B: {" << B_.x << "," << B_.y << "}" << std::endl;
  std::cout << "Coordinates of vertex C: {" << C_.x << "," << C_.y << "}" << std::endl;
  std::cout << "Center of triangle: {" << centerpos_.x << "," << centerpos_.y << "}" << std::endl;
}
