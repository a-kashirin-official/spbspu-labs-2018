#include "triangle.hpp"
#include <stdexcept>
#include <algorithm>
#include <math.h>


Triangle::Triangle(const point_t & A, const point_t & B, const point_t & C):
A_(A),
B_(B),
C_(C),
centre_({ ((A.x + B.x + C.x) / 3.0),
  ((A.y + B.y + C.y) / 3.0) })
{
  double AB = sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));
  double BC = sqrt(pow(C.x - B.x, 2) + pow(C.y - B.y, 2));
  double AC = sqrt(pow(C.x - A.x, 2) + pow(C.y - A.y, 2));

  if (AB + BC <= AC)
  {
      throw std::invalid_argument("(AB + BC) mustn't be <= AC");
  }
  else if (AC + BC <= AB)
  {
    throw std::invalid_argument("(AC + BC) mustn't be <= AB");
  }
  else if (AB + AC <= BC)
  {
    throw std::invalid_argument("(AB + AC) mustn't be <= BC");
  }
}
    
double Triangle::getArea() const noexcept
{
  return (abs((((A_.x - C_.x) * (B_.y - C_.y))
    - ((A_.y - C_.y) * (B_.x - C_.x))) / 2.0));
}
    
rectangle_t Triangle::getFrameRect() const noexcept
{
  double width = std::max(std::max(A_.x, B_.x), C_.x) 
    - std::min(std::min(A_.x, B_.x), C_.x);
  double height = std::max(std::max(A_.y, B_.y), C_.y) 
    - std::min(std::min(A_.y, B_.y), C_.y);

  double shiftX = width / 2.0 - (centre_.x - std::min(std::min(A_.x, B_.x), C_.x));
  double shiftY = height / 2.0 - (centre_.y - std::min(std::min(A_.y, B_.y), C_.y));

  return rectangle_t{ width, height, { centre_.x + shiftX, centre_.y + shiftY } };
}

void Triangle::move(const point_t & point) noexcept
{  
  double dx = point.x - centre_.x;
  double dy = point.y - centre_.y;
    
  A_.x += dx;
  A_.y += dy;
  B_.x += dx;
  B_.y += dy;
  C_.x += dx;
  C_.y += dy;

  centre_ = point;
}
    
void Triangle::move(const double dx, const double dy) noexcept
{
  A_.x += dx;
  A_.y += dy;
  B_.x += dx;
  B_.y += dy;
  C_.x += dx;
  C_.y += dy;

  centre_.x += dx;
  centre_.y += dy;
}
