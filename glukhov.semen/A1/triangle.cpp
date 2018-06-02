#include "triangle.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

Triangle::Triangle(const point_t &AngelA, const point_t &AngelB, const point_t &AngelC):
pos_( {(AngelA.x + AngelB.x + AngelC.x) / 3  , (AngelA.y + AngelB.y + AngelC.y) / 3 }), //center of gravity
A_vertex(AngelA),
B_vertex(AngelB),
C_vertex(AngelC)
{
  if (getArea() == 0.0)
  {
    throw std::invalid_argument("Vertex are the same");
    //three points not lying on one straight line def
  }
}
void Triangle::setPoints(const point_t &AngelA, const point_t &AngelB, const point_t &AngelC)
{
  A_vertex = AngelA;
  B_vertex = AngelB;
  C_vertex = AngelC;
}
void Triangle::move(const double dx,const double dy)
{
  pos_.x += dx;
  pos_.y += dy;

  A_vertex.x += dx;
  A_vertex.y += dy;

  B_vertex.x += dx;
  B_vertex.y += dy;

  C_vertex.x += dx;
  C_vertex.y += dy;
}
double Triangle::getMin(const double &AngelA, const double &AngelB, const double &AngelC)
{
  double min = AngelA;
  if (AngelB < min)
  {
    min = AngelB;
  }
  if (AngelC < min)
  {
    min = AngelC;
  }
  return min;
}
double Triangle::getMax(const double &AngelA, const double &AngelB, const double &AngelC)
{
  double max = AngelA;
  if (AngelB > max)
  {
    max = AngelB;
  }
  if (AngelC > max)
  {
    max = AngelC;
  }
  return max;
}

rectangle_t Triangle::getFrameRect() const
{
  double max_x = getMax(A_vertex.x, B_vertex.x, C_vertex.x);
  double min_x = getMin(A_vertex.x, B_vertex.x, C_vertex.x);
  double max_y = getMax(A_vertex.y, B_vertex.y, C_vertex.y);
  double min_y = getMin(A_vertex.y, B_vertex.y, C_vertex.y);
  return { max_x - min_x, max_y - min_y, pos_ };
}
double Triangle::getArea() const
{
  return ((std::abs(((A_vertex.x - C_vertex.x) * (B_vertex.y - C_vertex.y)) - ((A_vertex.y - C_vertex.y) * (B_vertex.x - C_vertex.x))) / 2));
  //formula for triangles area is  S = 0.5 * |(x1-x2)*(y2-y3) - (x2-x3)*(y1-y3)|
}
void Triangle::move(const point_t &point)
{
  A_vertex.x += point.x - pos_.x;
  A_vertex.y += point.y - pos_.y;

  B_vertex.x += point.x - pos_.x;
  B_vertex.y += point.y - pos_.y;
  
  C_vertex.y += point.y - pos_.y;
  C_vertex.x += point.x - pos_.x;
  
  pos_ = point;
}

void Triangle::printShapeInfo() const
{
  std::cout << "Triangle inf:\n";
  std::cout << "middle: [" << pos_.x << "," << pos_.y << "]\n";
  std::cout << "Vertex A: [" << A_vertex.x << "," << A_vertex.y << "]\n";
  std::cout << "Vertex B: [" << B_vertex.x << "," << B_vertex.y << "]\n";
  std::cout <<
               "Vertex C: [" << C_vertex.x << "," << C_vertex.y << "]\n";
}

