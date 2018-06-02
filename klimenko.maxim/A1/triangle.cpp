#include "triangle.hpp"
#include <stdexcept>
#include <math.h>
#include <algorithm>


Triangle::Triangle(const point_t & A, const point_t & B, const point_t & C):
A_(A),
B_(B),
C_(C),
centre_({ ((A.x + B.x + C.x) / 3.0), ((A.y + B.y + C.y) / 3.0) })
{
}

double Triangle::getArea() const noexcept
{
  return (abs((((A_.x - C_.x) * (B_.y - C_.y)) - ((A_.y - C_.y) * (B_.x - C_.x))) / 2.0));
}

rectangle_t Triangle::getFrameRect() const noexcept
{
  double width = std::max(std::max(A_.x, B_.x), C_.x) - std::min(std::min(A_.x, B_.x), C_.x);
  double height = std::max(std::max(A_.y, B_.y), C_.y) - std::min(std::min(A_.y, B_.y), C_.y);

  double shiftX = width / 2.0 - (centre_.x - std::min(std::min(A_.x, B_.x), C_.x));
  double shiftY = height / 2.0 - (centre_.y - std::min(std::min(A_.y, B_.y), C_.y));

  return rectangle_t{ width, height, { centre_.x + shiftX, centre_.y + shiftY } };
}

void Triangle::move(const point_t & point) noexcept
{
  double dx, dy;

  dx = point.x - centre_.x;
  dy = point.y - centre_.y;

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
