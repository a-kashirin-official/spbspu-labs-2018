#include <iostream>
#include <cmath>
#include "triangle.hpp"

Triangle::Triangle(const point_t &pos_a, const point_t &pos_b, const point_t &pos_c):
  pos_({(pos_a.x + pos_b.x + pos_c.x) / 3, (pos_a.y + pos_b.y + pos_c.y) / 3}),
  pos_a_(pos_a),
  pos_b_(pos_b),
  pos_c_(pos_c)
{}

double Triangle::getMin(double first, double second, double third) const
{
  double min = first;

  if (second < min)
  {
    min = second;
  }

  if (third < min)
  {
    min = third;
  }

  return min;
}

double Triangle::getMax(double first, double second, double third) const
{
  double max = first;

  if (second > max)
  {
    max = second;
  }

  if (third > max)
  {
    max = third;
  }

  return max;
}

double Triangle::getArea() const
{
  return ((std::abs(((pos_a_.x - pos_c_.x) * (pos_b_.y - pos_c_.y)) - ((pos_a_.y - pos_c_.y) * (pos_b_.x - pos_c_.x))) / 2));
}

rectangle_t Triangle::getFrameRect() const
{
  double max_x = getMax(pos_a_.x, pos_b_.x, pos_c_.x);
  double min_x = getMin(pos_a_.x, pos_b_.x, pos_c_.x);
  double max_y = getMax(pos_a_.y, pos_b_.y, pos_c_.y);
  double min_y = getMin(pos_a_.y, pos_b_.y, pos_c_.y);
  return { max_x - min_x, max_y - min_y, pos_ };
}

void Triangle::move(const point_t &point)
{
  pos_a_.x += point.x - pos_.x;
  pos_b_.x += point.x - pos_.x;
  pos_c_.x += point.x - pos_.x;
  pos_a_.y += point.y - pos_.y;
  pos_b_.y += point.y - pos_.y;
  pos_c_.y += point.y - pos_.y;
  pos_ = point;
}

void Triangle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_a_.x += dx;
  pos_b_.x += dx;
  pos_c_.x += dx;
  pos_.y += dy;
  pos_a_.y += dy;
  pos_b_.y += dy;
  pos_c_.y += dy;
}

void Triangle::printShapeInfo() const
{
  std::cout << "Triangle info: ({" << pos_.x << ", " << pos_.y << "}, " 
    << "{" << pos_a_.x << ", " << pos_a_.y << "}, " 
    << "{" << pos_b_.x << ", " << pos_b_.y << "}, " 
    << "{" << pos_c_.x << ", " << pos_c_.y << "})\n";
}
