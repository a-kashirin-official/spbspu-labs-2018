#include "triangle.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>
using namespace ivanov;

Triangle::Triangle(const point_t &point1, const point_t &point2, const point_t &point3):
pos_({(point1.x + point2.x + point3.x) / 3, (point1.y + point2.y + point3.y) / 3}), //center of gravity of triangle
point1_(point1),
point2_(point2),
point3_(point3)
{
  if (getArea() == 0.0)
  {
    throw std::invalid_argument("Vertex are the same, enter different ones");
    //referring to definition "..three points not lying on one straight line.."
  }
}
point_t Triangle::getVertex1() const
{
  return point1_;
}
point_t Triangle::getVertex2() const
{
  return point2_;
}
point_t Triangle::getVertex3() const
{
  return point3_;
}
point_t Triangle::getCenter() const
{
  return pos_;
}
void Triangle::setPoints(const point_t &point1, const point_t &point2, const point_t &point3)
{
  point1_ = point1;
  point2_ = point2;
  point3_ = point3;
}
double Triangle::getMax(const double &point1, const double &point2, const double &point3)
{
  double max = point1; //if A is max
  if (point2 > max)//comparision with B
  {
    max = point2;
  }
  if (point3 > max)//comparision with c
  {
    max = point3;
  }
  return max;
}
double Triangle::getMin(const double &point1, const double &point2, const double &point3)
{
  double min = point1; //if A is min
  if (point2 < min)  //comparision with B
  {
    min = point2;  
  }
  if (point3 < min)  //comparision with C
  {
    min = point3;  
  }
  return min;
}

double Triangle::getArea() const
{
  return ((std::abs(((point1_.x - point3_.x) * (point2_.y - point3_.y)) - ((point1_.y - point3_.y) * (point2_.x - point3_.x))) / 2));
  //formula for triangles area by vertex coordinates is  S = 0.5 * |(x1-x2)*(y2-y3) - (x2-x3)*(y1-y3)|
}
rectangle_t Triangle::getFrameRect() const
{
  double max_x = getMax(point1_.x, point2_.x, point3_.x);
  double min_x = getMin(point1_.x, point2_.x, point3_.x);

  double max_y = getMax(point1_.y, point2_.y, point3_.y);
  double min_y = getMin(point1_.y, point2_.y, point3_.y);

  return { pos_, max_x - min_x, max_y - min_y };
}
void Triangle::move(const point_t &point)
{
  point1_.x += point.x - pos_.x;
  point1_.y += point.y - pos_.y;

  point2_.x += point.x - pos_.x;
  point2_.y += point.y - pos_.y;

  point3_.x += point.x - pos_.x; 
  point3_.y += point.y - pos_.y;

  pos_ = point;
}
void Triangle::move(const double dx,const double dy)
{
  pos_.x += dx;
  pos_.y += dy;

  point1_.x += dx;
  point1_.y += dy;

  point2_.x += dx;
  point2_.y += dy;

  point3_.x += dx;  
  point3_.y += dy;
}
void Triangle::scale(const double ratio){
  if (ratio < 0.0)
  {
    throw std::invalid_argument("Ratio can't be negative");
  }
  point1_.x = pos_.x + (point1_.x - pos_.x) * ratio;
  point1_.y = pos_.y + (point1_.y - pos_.y) * ratio;

  point2_.x = pos_.x + (point2_.x - pos_.x) * ratio;
  point2_.y = pos_.y + (point2_.y - pos_.y) * ratio;

  point3_.x = pos_.x + (point3_.x - pos_.x) * ratio;
  point3_.y = pos_.y + (point3_.y - pos_.y) * ratio;
}
void Triangle::show() const
{
  std::cout << "Triangle info:\n";
  std::cout << "Centre: {" << pos_.x << "," << pos_.y << "}\n";
  std::cout << "Vertex A: {" << point1_.x << "," << point1_.y << "}\n";
  std::cout << "Vertex B: {" << point2_.x << "," << point2_.y << "}\n";
  std::cout << "Vertex C: {" << point3_.x << "," << point3_.y << "}\n";
}


