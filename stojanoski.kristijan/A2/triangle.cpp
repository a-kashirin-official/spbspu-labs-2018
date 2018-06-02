#include "triangle.hpp"
#include <algorithm>
#include <stdexcept>
#include <math.h>

using namespace stojanoski;

Triangle::Triangle(const point_t & p1, const point_t & p2, const point_t & p3) :
  a_(p1),
  b_(p2),
  c_(p3)
{
  if (getArea() <= 0.0)
  {
    throw std::invalid_argument("Invalid Triangle parameters!");
  }
}
double Triangle::getArea() const
{
  double ab = getDistance(a_, b_);
  double ac = getDistance(a_, c_);
  double bc = getDistance(b_, c_);
  double s = (ab + ac + bc) / 2;
  return std::sqrt(s*(s - ab)*(s - ac)*(s - bc));
}
rectangle_t Triangle::getFrameRect() const
{
  double left = std::min(std::min(a_.x, b_.x), c_.x);
  double bot = std::min(std::min(a_.y, b_.y), c_.y);
  double h = fabs(std::max(std::max(a_.y, b_.y), c_.y) - bot);
  double w = fabs(std::max(std::max(a_.x, b_.x), c_.x) - left);
  return rectangle_t{getCenter(), w, h };
}
void Triangle::move(double dx, double dy) 
{
  a_.x += dx;
  b_.x += dx;
  c_.x += dx;
  a_.y += dy;
  b_.y += dy;
  c_.y += dy;
}
void Triangle::move(const point_t & p)
{
  move(p.x - getCenter().x, p.y - getCenter().y);
}
point_t Triangle::getCenter() const
{
  return point_t{ (a_.x + b_.x + c_.x) / 3, (a_.y + b_.y + c_.y) / 3 };
}
double Triangle::getDistance(const point_t & p1, const point_t & p2)
{
  return std::sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}
void Triangle::scale(double k)
{
  if (k < 0.0)
  {
    throw std::invalid_argument("Invalid Triangle scale coefficient!");
  }
  point_t center = getCenter();
  a_.x = center.x + (a_.x - center.x) * k;
  a_.y = center.y + (a_.y - center.y) * k;
  b_.x = center.x + (b_.x - center.x) * k;
  b_.y = center.y + (b_.y - center.y) * k;
  c_.x = center.x + (c_.x - center.x) * k;
  c_.y = center.y + (c_.y - center.y) * k;
}
