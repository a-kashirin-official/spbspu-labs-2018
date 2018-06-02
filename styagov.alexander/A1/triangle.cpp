#include "triangle.hpp"

#include <algorithm>
#include <stdexcept>
#include <cmath>

Triangle::Triangle(const point_t & a, const point_t & b, const point_t & c):
  vertices_{ a, b, c }
{

}

void Triangle::setVertexAtIndex(const int index, const point_t & vertex)
{
  if ((index < 0) || (index > 2))
  {
    throw std::invalid_argument("Triangle: Vertex index must be 0, 1 or 2");
  }

  vertices_[index] = vertex;
}

point_t Triangle::getVertexAtIndex(const int index) const
{
  if ((index < 0) || (index > 2))
  {
    throw std::invalid_argument("Triangle: Vertex index must be 0, 1 or 2");
  }

  return vertices_[index];
}

point_t Triangle::getPos() const
{
  double x = (vertices_[0].x + vertices_[1].x + vertices_[2].x) / 3;
  double y = (vertices_[0].y + vertices_[1].y + vertices_[2].y) / 3;
  return { x, y };
}

double Triangle::getArea() const
{
  double ax = vertices_[1].x - vertices_[0].x;
  double ay = vertices_[1].y - vertices_[0].y;
  double aLength = sqrt(ax * ax + ay * ay);

  double bx = vertices_[2].x - vertices_[1].x;
  double by = vertices_[2].y - vertices_[1].y;
  double bLength = sqrt(bx * bx + by * by);

  double cx = vertices_[2].x - vertices_[0].x;
  double cy = vertices_[2].y - vertices_[0].y;
  double cLength = sqrt(cx * cx + cy * cy);

  double p = (aLength + bLength + cLength) / 2;

  return sqrt(p * (p - aLength) * (p - bLength) * (p - cLength));
}

rectangle_t Triangle::getFrameRect() const
{
  auto widthResult = std::minmax({ vertices_[0].x, vertices_[1].x, vertices_[2].x });
  double left = widthResult.first;
  double right = widthResult.second;

  auto heightResult = std::minmax({ vertices_[0].y, vertices_[1].y, vertices_[2].y });
  double bottom = heightResult.first;
  double top = heightResult.second;

  double width = right - left;
  double height = top - bottom;
  point_t pos = { left + (width / 2), bottom + (height / 2) };

  return { pos, width, height };
}

void Triangle::move(const point_t &pos)
{
  point_t oldPos = getPos();
  vertices_[0].x += pos.x - oldPos.x;
  vertices_[0].y += pos.y - oldPos.y;

  vertices_[1].x += pos.x - oldPos.x;
  vertices_[1].y += pos.y - oldPos.y;

  vertices_[2].x += pos.x - oldPos.x;
  vertices_[2].y += pos.y - oldPos.y;
}

void Triangle::move(const double dx, const double dy)
{
  vertices_[0].x += dx;
  vertices_[0].y += dy;

  vertices_[1].x += dx;
  vertices_[1].y += dy;

  vertices_[2].x += dx;
  vertices_[2].y += dy;
}
