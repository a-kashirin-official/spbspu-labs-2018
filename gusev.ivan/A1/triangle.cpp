#include "triangle.hpp"
#include <iostream>
#include <cmath>

Triangle::Triangle(const point_t & a, const point_t & b, const point_t & c):
  a_(a),
  b_(b),
  c_(c)
{}

double Triangle::getArea() const
{
  return fabs((a_.x - c_.x) * (b_.y - c_.y) - (b_.x - c_.x) * (a_.y - c_.y)) * 0.5;
}

rectangle_t Triangle::getFrameRect() const
{
  double Xmin = a_.x < b_.x ? (a_.x < c_.x ? a_.x : c_.x) : (b_.x < c_.x ? b_.x :c_.x);
  double Xmax = a_.x > b_.x ? (a_.x > c_.x ? a_.x : c_.x) : (b_.x > c_.x ? b_.x :c_.x);
  double Ymin = a_.y < b_.y ? (a_.y < c_.y ? a_.y : c_.y) : (b_.y < c_.y ? b_.y :c_.y);
  double Ymax = a_.y > b_.y ? (a_.y < c_.y ? a_.y : c_.y) : (b_.y > c_.y ? b_.y :c_.y);
  return { (Xmax - Xmin), (Ymax - Ymin), { ((Xmax - Xmin) / 2 + Xmin), ((Ymax - Ymin) / 2 + Ymin) } };
}

void Triangle::move(const point_t &point)
{
  point_t center = { (a_.x + b_.x + c_.x) / 3, (a_.y + b_.y + c_.y) / 3 };
  a_ = { a_.x + (point.x - center.x), a_.x + (point.y - center.y) };
  b_ = { b_.x + (point.x - center.x), b_.x + (point.y - center.y) };
  c_ = { c_.x + (point.x - center.x), c_.x + (point.y - center.y) };
}

void Triangle::move(const double dx, const double dy)
{
  a_ = { a_.x + dx, a_.y + dy };
  c_ = { c_.x + dx, c_.y + dy };
  b_ = { b_.x + dx, b_.y + dy };
}
