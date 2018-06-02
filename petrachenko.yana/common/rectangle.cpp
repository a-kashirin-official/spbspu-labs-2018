#include "rectangle.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace petrachenko;

Rectangle::Rectangle(const double width, const double height, const point_t &center):
  vertices_{{center.x - width / 2, center.y - height / 2}, // left bottom vertex
            {center.x - width / 2, center.y + height / 2}, // left top vertex
            {center.x + width / 2, center.y + height / 2}, // right top vertex
            {center.x + width / 2, center.y - height / 2}} // right bottom vertex
{
  if (width < 0.0){
    throw std::invalid_argument("Invalid_rectangle_width");
  }
  if (height < 0.0){
    throw std::invalid_argument("Invalid_rectangle_height");
  }
}

double Rectangle::getArea() const
{
  return (getDistance(vertices_[3], vertices_[0]) * getDistance(vertices_[1], vertices_[0]));
}

rectangle_t Rectangle::getFrameRect() const
{
  double maxX = vertices_[0].x;
  double maxY = vertices_[0].y;
  double minX = vertices_[0].x;
  double minY = vertices_[0].y;

  for (auto vertex : vertices_) {
    maxX = (vertex.x > maxX) ? vertex.x : maxX;
    maxY = (vertex.y > maxY) ? vertex.y : maxY;
    minX = (vertex.x < minX) ? vertex.x : minX;
    minY = (vertex.y < minY) ? vertex.y : minY;
  }
  return {maxX - minX, maxY - minY, {minX + (maxX - minX) / 2, minY + (maxY - minY) / 2}};
}

void Rectangle::move(const point_t &p)
{
  const double dx = p.x - getPos().x;
  const double dy = p.y - getPos().y;
  move(dx, dy);
}

void Rectangle::move(const double dx, const double dy)
{
  for (auto &vertex : vertices_) {
    vertex.x += dx;
    vertex.y += dy;
  }
}

double Rectangle::getDistance(const point_t &point1, const point_t &point2) const
{
  return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
}

void Rectangle::scale(double coefficient)
{
  if (coefficient < 0.0)
  {
    throw std::invalid_argument("Invalid_scale_coefficient_for_rectangle");
  }
  const point_t center = getPos();
  for (auto &vertex : vertices_) {
    vertex.x = center.x + (vertex.x - center.x) * coefficient;
    vertex.y = center.y + (vertex.y - center.y) * coefficient;
  }
}

point_t Rectangle::getPos() const
{
 return {(vertices_[0].x + vertices_[2].x) / 2, (vertices_[0].y + vertices_[2].y) / 2};
}

void Rectangle::rotate(double alpha)
{
  double rad = alpha * M_PI / 180;
  const double x = getPos().x;
  const double y = getPos().y;
  for (auto &vertex : vertices_) {
    const double dx = vertex.x;
    const double dy = vertex.y;
    vertex.x = x + (dx - x) * cos(rad) - (dy - y) * sin(rad);
    vertex.y = y + (dx - x) * sin(rad) + (dy - y) * cos(rad);
  }
}

void Rectangle::print() const
{
  std::cout << "Rectangle:" << std::endl;
  std::cout << "Width is " << getDistance(vertices_[3], vertices_[0]) << std::endl;
  std::cout << "Height is " << getDistance(vertices_[1], vertices_[0]) << std::endl;
  std::cout << "Center is (" << getPos().x << "," << getPos().y << ")" << std::endl;
  std::cout << "Width of the frame is " << getFrameRect().width << std::endl;
  std::cout << "Height of the frame is " << getFrameRect().height << std::endl;
  std::cout << "Center of the frame is (" << getFrameRect().pos.x << "," << getFrameRect().pos.y << ")" << std::endl;
  std::cout << "Area is " << getArea() << std::endl;
  std::cout << std::endl;
}

