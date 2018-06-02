#include "triangle.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>

Triangle::Triangle(const point_t & A, const point_t & B, const point_t & C):
  Shape({(A.x + B.x + C.x) / 3.0, (A.y + B.y + C.y) / 3.0})
{
  double AB = sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));
  double BC = sqrt(pow(C.x - B.x, 2) + pow(C.y - B.y, 2));
  double AC = sqrt(pow(C.x - A.x, 2) + pow(C.y - A.y, 2));

  if (AB + BC <= AC)
  {
    throw std::invalid_argument("Invalid point's of triangle! AB + BC <= AC");
  }
  else if (AB + AC <= BC)
  {
    throw std::invalid_argument("Invalid point's of triangle! AB + AC <= BC");
  }
  else if (AC + BC <= AB)
  {
    throw std::invalid_argument("Invalid point's of triangle! AC + BC <= AB");
  }
  A_ = A;
  B_ = B;
  C_ = C;
};

double Triangle::getArea() const
{
  return abs(0.5 * ((A_.x - C_.x) * (B_.y - C_.y) 
                    - (B_.x - C_.x) * (A_.y - C_.y)));
};

rectangle_t Triangle::getFrameRect() const
{
  double width = std::max(std::max(A_.x, B_.x), C_.x) 
                 - std::min(std::min(A_.x, B_.x), C_.x);
  double height = std::max(std::max(A_.y, B_.y), C_.y) 
                  - std::min(std::min(A_.y, B_.y), C_.y);
  double plusToX = width / 2.0 - (pos_.x - std::min(std::min(A_.x, B_.x), C_.x));
  double plusToY = height / 2.0 - (pos_.y - std::min(std::min(A_.y, B_.y), C_.y));
  return rectangle_t{width, height, {pos_.x + plusToX, pos_.y + plusToY}};
};

void Triangle::move(const point_t & pos)
{
  A_.x -= pos_.x - pos.x;
  A_.y -= pos_.y - pos.y;
  B_.x -= pos_.x - pos.x;
  B_.y -= pos_.y - pos.y;
  C_.x -= pos_.x - pos.x;
  C_.y -= pos_.y - pos.y;
  pos_ = pos;
};

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
};
