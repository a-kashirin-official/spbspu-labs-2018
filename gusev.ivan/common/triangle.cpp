#include "triangle.hpp"
#include <cmath>
#include <stdexcept>

gusev::Triangle::Triangle(const point_t & a, const point_t & b, const point_t & c):
  a_(a),
  b_(b),
  c_(c),
  center_({ (a_.x + b_.x + c_.x) / 3, (a_.y + b_.y + c_.y) / 3 })
{
  if ((fabs((a_.x - c_.x) * (b_.y - c_.y) - (b_.x - c_.x) * (a_.y - c_.y)) * 0.5) == 0)
  {
    throw std::invalid_argument("Invalid argument");
  }
}

double gusev::Triangle::getArea() const
{
  return fabs((a_.x - c_.x) * (b_.y - c_.y) - (b_.x - c_.x) * (a_.y - c_.y)) * 0.5;
}

gusev::rectangle_t gusev::Triangle::getFrameRect() const
{
  double Xmin = a_.x < b_.x ? (a_.x < c_.x ? a_.x : c_.x) : (b_.x < c_.x ? b_.x :c_.x);
  double Xmax = a_.x > b_.x ? (a_.x > c_.x ? a_.x : c_.x) : (b_.x > c_.x ? b_.x :c_.x);
  double Ymin = a_.y < b_.y ? (a_.y < c_.y ? a_.y : c_.y) : (b_.y < c_.y ? b_.y :c_.y);
  double Ymax = a_.y > b_.y ? (a_.y < c_.y ? a_.y : c_.y) : (b_.y > c_.y ? b_.y :c_.y);
  return { (Xmax - Xmin), (Ymax - Ymin), { ((Xmax - Xmin) / 2 + Xmin), ((Ymax - Ymin) / 2 + Ymin) } };
}

void gusev::Triangle::move(const point_t &point)
{
  center_.x = point.x;
  center_.y = point.y;
  a_ = { a_.x + (point.x - center_.x), a_.x + (point.y - center_.y) };
  b_ = { b_.x + (point.x - center_.x), b_.x + (point.y - center_.y) };
  c_ = { c_.x + (point.x - center_.x), c_.x + (point.y - center_.y) };
}

void gusev::Triangle::move(const double dx, const double dy)
{
  a_ = { a_.x + dx, a_.y + dy };
  c_ = { c_.x + dx, c_.y + dy };
  b_ = { b_.x + dx, b_.y + dy };
  center_.x += dx;
  center_.y += dy;
}

void gusev::Triangle::scale(const double coef)
{
  if (coef <= 0)
  {
    throw std::invalid_argument("Invalid coef");
  }
  a_ = { (a_.x - center_.x) * coef + center_.x, (a_.y - center_.y) * coef + center_.y };
  b_ = { (b_.x - center_.x) * coef + center_.x, (b_.y - center_.y) * coef + center_.y };
  c_ = { (c_.x - center_.x) * coef + center_.x, (c_.y - center_.y) * coef + center_.y };
}

gusev::point_t gusev::Triangle::getCenter() const
{
  return center_;
}
