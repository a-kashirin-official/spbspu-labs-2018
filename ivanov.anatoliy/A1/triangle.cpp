#include <iostream>
#include <cmath>
#include <cassert>
#include "triangle.hpp"

Triangle::Triangle(const point_t & vertexA, const point_t & vertexB, const point_t & vertexC):
  vertexA_(vertexA),
  vertexB_(vertexB),
  vertexC_(vertexC)
{
  center_.x = (vertexA_.x+vertexB_.x+vertexC_.x)/3.0;
  center_.y = (vertexA_.y+vertexB_.y+vertexC_.y)/3.0;
}

double Triangle::getArea() const
{
  return std::abs((vertexA_.x-vertexC_.x)*(vertexB_.y-vertexC_.y)-(vertexB_.x-vertexC_.x)*(vertexA_.y-vertexC_.y))/2;
}

rectangle_t Triangle::getFrameRect() const
{
  double minx(std::min(std::min(vertexA_.x,vertexB_.x),vertexC_.x));
  double maxx(std::max(std::max(vertexA_.x,vertexB_.x),vertexC_.x));
  double miny(std::min(std::min(vertexA_.y,vertexB_.y),vertexC_.y));
  double maxy(std::max(std::max(vertexA_.y,vertexB_.y),vertexC_.y));
  return rectangle_t{{(minx+maxx)/2,(miny+maxy)/2},maxx-minx,maxy-miny};
}

void Triangle::move(const point_t & transferPoint)
{
  vertexA_.x += transferPoint.x - center_.x;
  vertexA_.y += transferPoint.y - center_.y;
  vertexB_.x += transferPoint.x - center_.x;
  vertexB_.y += transferPoint.y - center_.y;
  vertexC_.x += transferPoint.x - center_.x;
  vertexC_.y += transferPoint.y - center_.y;
  center_ = transferPoint;
}

void Triangle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
  vertexA_.x += dx;
  vertexA_.y += dy;
  vertexB_.x += dx;
  vertexB_.y += dy;
  vertexC_.x += dx;
  vertexC_.y += dy;
}

void Triangle::printCurrentInfo() const
{
  std::cout << "Triangle center (x,y): " << center_.x << ", " << center_.y << std::endl;
  std::cout << "Triangle vertex A (x,y): " << vertexA_.x << ", " << vertexA_.y << std::endl;
  std::cout << "Triangle vertex B (x,y): " << vertexB_.x << ", " << vertexB_.y << std::endl;
  std::cout << "Triangle vertex C (x,y): " << vertexC_.x << ", " << vertexC_.y << std::endl;
};
