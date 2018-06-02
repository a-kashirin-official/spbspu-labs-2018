#include "triangle.hpp"
#include <iostream>
#include <cmath>

Triangle::Triangle(const point_t &a, const point_t &b, const point_t &c):
  a_(a),
  b_(b),
  c_(c)
{
  centre_={(a_.x+b_.x+c_.x)/3,(a_.y+b_.y+c_.y)/3};
}

double Triangle::getArea() const
{
  return fabs(((a_.x - c_.x) * (b_.y - c_.y) - (b_.x - c_.x) * (a_.y - c_.y))) *0.5;
};

rectangle_t Triangle::getFrameRect() const
{
  double maxY = a_.y > b_.y ? (a_.y > c_.y ? a_.y : c_.y) : (b_.y > c_.y ? b_.y : c_.y);
  double minY = a_.y < b_.y ? (a_.y < c_.y ? a_.y : c_.y) : (b_.y < c_.y ? b_.y : c_.y);
  double maxX = a_.x > b_.x ? (a_.x > c_.x ? a_.x : c_.x) : (b_.x > c_.x ? b_.x : c_.x);
  double minX = a_.x < b_.x ? (a_.x < c_.x ? a_.x : c_.x) : (b_.x < c_.x ? b_.x : c_.x);
  return {maxX - minX, maxY - minY, {minX + (maxX - minX)/2, minY + (maxY - minY)/2}};
};

void Triangle::move(const point_t &poss)
{
  centre_={poss.x,poss.y};
  move(poss.x - (a_.x+b_.x+c_.x)/3, poss.y -  (a_.y+b_.y+c_.y)/3);
};

void Triangle::move(const double dx,const double dy)
{
  a_ = {a_.x + dx, a_.y + dy};
  b_ = {b_.x + dx, b_.y + dy};
  c_ = {c_.x + dx, c_.y + dy};
  centre_={(a_.x+b_.x+c_.x)/3,(a_.y+b_.y+c_.y)/3};
};
point_t Triangle::getCenterPoint() const
{
  return centre_;
}
void Triangle::info() const
{
  std::cout << "A: x = " << a_.x << " y = "<< a_.y << std::endl;
  std::cout << "B: x = " << b_.x << " y = "<< b_.y << std::endl;
  std::cout << "C: x = " << c_.x << " y = "<< c_.y << std::endl;
};
