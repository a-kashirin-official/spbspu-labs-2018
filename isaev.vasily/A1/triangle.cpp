#include "triangle.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

Triangle::Triangle(const point_t &A, const point_t &B, const point_t &C):
pos_( {(A.x + B.x + C.x) / 3  , (A.y + B.y + C.y) / 3 }), //center of gravity of triangle
A_vertex(A),
B_vertex(B),
C_vertex(C)
{
  if (getArea() == 0.0)
  {
    throw std::invalid_argument("Vertex are the same, enter different ones");
    //referring to definition "..three points not lying on one straight line.."
  }
}
void Triangle::setPoints(const point_t &A, const point_t &B, const point_t &C)
{
  A_vertex = A;
  B_vertex = B;
  C_vertex = C;
}
double Triangle::getMin(const double &A, const double &B, const double &C)
{
  double min = A; //if A is min
  if (B < min)  //comparision with B
  {
    min = B;    
  }
  if (C < min)  //comparision with C
  {
    min = C;    
  }
  return min;
}
double Triangle::getMax(const double &A, const double &B, const double &C)
{
  double max = A; //if A is max
  if (B > max)  //comparision with B
  {
    max = B;
  }
  if (C > max)  //comparision with c
  {
    max = C;
  }
  return max;
}
double Triangle::getArea() const
{
  return ((std::abs(((A_vertex.x - C_vertex.x) * (B_vertex.y - C_vertex.y)) - ((A_vertex.y - C_vertex.y) * (B_vertex.x - C_vertex.x))) / 2));
  //formula for triangles area by vertex coordinates is  S = 0.5 * |(x1-x2)*(y2-y3) - (x2-x3)*(y1-y3)|
}
rectangle_t Triangle::getFrameRect() const
{
  double max_x = getMax(A_vertex.x, B_vertex.x, C_vertex.x);
  double min_x = getMin(A_vertex.x, B_vertex.x, C_vertex.x);
  double max_y = getMax(A_vertex.y, B_vertex.y, C_vertex.y);
  double min_y = getMin(A_vertex.y, B_vertex.y, C_vertex.y);
  return { max_x - min_x, max_y - min_y, pos_ };
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
void Triangle::printShapeInfo() const
{
  std::cout << "Triangle info:\n";
  std::cout << "Centre: {" << pos_.x << "," << pos_.y << "}\n";
  std::cout << "Vertex A: {" << A_vertex.x << "," << A_vertex.y << "}\n";
  std::cout << "Vertex B: {" << B_vertex.x << "," << B_vertex.y << "}\n";
  std::cout << "Vertex C: {" << C_vertex.x << "," << C_vertex.y << "}\n";
}

