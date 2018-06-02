#include <iostream>
#include <algorithm>
#include <cmath>

#include "triangle.hpp"

Triangle::Triangle(const point_t& sd_a, const point_t& sd_b, const point_t& sd_c) :
  pos({ (sd_a.x + sd_b.x + sd_c.x) / 3, (sd_a.y + sd_b.y + sd_c.y) / 3 })
{
  double epsilon = 0.001;
  A_ = sd_a;
  B_ = sd_b;
  C_ = sd_c;

  if ( std::abs(getArea() - 0.0) < epsilon)
  {
    std::cerr << "wrong arguments" << std::endl;
  }
}

double Triangle::getArea() const
{
  return (0.5 * std::abs((A_.x - C_.x) * (B_.y - C_.y) - (B_.x - C_.x) * (A_.y - C_.y)));
}

rectangle_t Triangle::getFrameRect() const
{
  double max_x = std::max(A_.x, std::max(B_.x ,C_.x));
  double max_y = std::max(A_.y, std::max(B_.y ,C_.y));

  double min_x = std::min(A_.x, std::min(B_.x ,C_.x));
  double min_y = std::min(A_.y, std::min(B_.y ,C_.y));

  return{ max_x - min_x, max_y - min_y,{ min_x, min_y } };
}

void Triangle::move(const point_t &pos_n)
{
  double dx = pos_n.x - pos.x;
  double dy = pos_n.y - pos.y;

  pos = pos_n;

  A_.x = A_.x + dx;
  A_.y = A_.y + dy;

  B_.x = B_.x + dx;
  B_.y = B_.y + dy;

  C_.x = C_.x + dx;
  C_.y = C_.y + dy;
}

void Triangle::move(double dx, double dy)
{
  pos.x = pos.x + dx;
  pos.y = pos.y + dy;

  A_.x = A_.x + dx;
  A_.y = A_.y + dy;

  B_.x = B_.x + dx;
  B_.y = B_.y + dy;

  C_.x = C_.x + dx;
  C_.y = C_.y + dy;
}
