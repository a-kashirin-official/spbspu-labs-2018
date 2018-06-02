#include "triangle.hpp"

#include <algorithm>
#include <math.h>
#include <stdexcept>

using namespace styagov;

styagov::Triangle::Triangle(const styagov::point_t & a, const styagov::point_t & b, const styagov::point_t & c) noexcept:
  vertices_{ a, b, c }
{

}

void styagov::Triangle::setVertexAtIndex(const int index, const styagov::point_t & vertex)
{
  if (index < 0)
  {
    throw std::invalid_argument("Triangle: Vertex index must be 0, 1 or 2");
  }
  if (index > 2)
  {
    throw std::invalid_argument("Triangle: Vertex index must be 0, 1 or 2");
  }

  vertices_[index] = vertex;
}

styagov::point_t styagov::Triangle::getVertexAtIndex(const int index) const
{
  if (index < 0)
  {
    throw std::invalid_argument("Triangle: Vertex index must be 0, 1 or 2");
  }
  if (index > 2)
  {
    throw std::invalid_argument("Triangle: Vertex index must be 0, 1 or 2");
  }

  return vertices_[index];
}

styagov::point_t styagov::Triangle::getPos() const noexcept
{
  double x = (vertices_[0].x + vertices_[1].x + vertices_[2].x) / 3;
  double y = (vertices_[0].y + vertices_[1].y + vertices_[2].y) / 3;
  
  return { x, y };
}

double styagov::Triangle::getArea() const noexcept
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

styagov::rectangle_t styagov::Triangle::getFrameRect() const noexcept
{
  auto widthResult = std::minmax({ vertices_[0].x, vertices_[1].x, vertices_[2].x });
  double left = widthResult.first;
  double right = widthResult.second;

  auto heightResult = std::minmax({ vertices_[0].y, vertices_[1].y, vertices_[2].y });
  double bottom = heightResult.first;
  double top = heightResult.second;

  double width = right - left;
  double height = top - bottom;
  styagov::point_t pos = { left + (width / 2), bottom + (height / 2) };

  return { pos, width, height };
}

void styagov::Triangle::move(const styagov::point_t & pos) noexcept
{
  styagov::point_t oldPos = getPos();
  vertices_[0].x += pos.x - oldPos.x;
  vertices_[0].y += pos.y - oldPos.y;

  vertices_[1].x += pos.x - oldPos.x;
  vertices_[1].y += pos.y - oldPos.y;

  vertices_[2].x += pos.x - oldPos.x;
  vertices_[2].y += pos.y - oldPos.y;
}

void styagov::Triangle::move(const double dx, const double dy) noexcept
{
  vertices_[0].x += dx;
  vertices_[0].y += dy;

  vertices_[1].x += dx;
  vertices_[1].y += dy;

  vertices_[2].x += dx;
  vertices_[2].y += dy;
}

void styagov::Triangle::scale(const double ratio)
{
  if (ratio < 0.0)
  {
    throw std::invalid_argument("Triangle: Ratio value must be non-negative");
  }

  styagov::point_t pos = getPos();
  for(styagov::point_t & vertex : vertices_)
  {
    vertex.x = vertex.x * ratio;
    vertex.y = vertex.y * ratio;
  }

  move(pos); // returning back
}

void styagov::Triangle::rotate(const double alpha) noexcept
{
  // translating degrees into radians
  const double sinAlpha = sin(alpha * M_PI / 180.0);
  const double cosAlpha = cos(alpha * M_PI / 180.0);
  const styagov::point_t center = this->getPos();

  for(size_t i = 0; i < 3; i++)
  {
    const double x = vertices_[i].x;
    const double y = vertices_[i].y;

    vertices_[i] = { 
      (x - center.x) * cosAlpha - (y - center.y) * sinAlpha + center.x,
      (x - center.x) * sinAlpha - (y - center.y) * cosAlpha + center.y 
    };
  }
}
