#include "rectangle.hpp"
#include <iostream>
#include <cmath>

using namespace lashchenov;

Rectangle::Rectangle(const double width, const double height, const point_t & center) :
  vertices_{{center.x - width / 2, center.y - height / 2}, // left bottom vertex
            {center.x - width / 2, center.y + height / 2}, // left top vertex
            {center.x + width / 2, center.y + height / 2}, // right top vertex
            {center.x + width / 2, center.y - height / 2}} // right bottom vertex
{
  if (width < 0) {
    throw std::invalid_argument("Rectangle width can't be < 0");
  }
  if (height < 0) {
    throw std::invalid_argument("Rectangle height can't be < 0");
  }
}

Rectangle::Rectangle(const double width, const double height, const double x, const double y) :
  vertices_{{x - width / 2, y - height / 2}, // left bottom vertex
            {x - width / 2, y + height / 2}, // left top vertex
            {x + width / 2, y + height / 2}, // right top vertex
            {x + width / 2, y - height / 2}} // right bottom vertex
{
  if (width < 0) {
    throw std::invalid_argument("Rectangle width can't be < 0");
  }
  if (height < 0) {
    throw std::invalid_argument("Rectangle height can't be < 0");
  }
}

double Rectangle::getArea() const
{
  return calcDistance(vertices_[3], vertices_[0]) * calcDistance(vertices_[1], vertices_[0]);
}

rectangle_t Rectangle::getFrameRect() const
{
  double MaxX = vertices_[0].x;
  double MaxY = vertices_[0].y;
  double MinX = vertices_[0].x;
  double MinY = vertices_[0].y;

  for (auto vertex : vertices_) {
    MaxX = (vertex.x > MaxX) ? vertex.x : MaxX;
    MaxY = (vertex.y > MaxY) ? vertex.y : MaxY;
    MinX = (vertex.x < MinX) ? vertex.x : MinX;
    MinY = (vertex.y < MinY) ? vertex.y : MinY;
  }
  return {MaxX - MinX, MaxY - MinY, {MinX + (MaxX - MinX) / 2, MinY + (MaxY - MinY) / 2}};
}

void Rectangle::move(const point_t & NewCenter)
{
  move(NewCenter.x - getCenter().x, NewCenter.y - getCenter().y);
}

void Rectangle::move(const double dx, const double dy)
{
  for (auto & vertex : vertices_) {
    vertex.x += dx;
    vertex.y += dy;
  }

}

void Rectangle::scale(const double multiplier)
{
  if (multiplier < 0) {
    throw std::invalid_argument("Scale multiplier for rectangle can't be < 0");
  }

  const point_t center = getCenter();
  for (auto & vertex : vertices_) {
    vertex.x = center.x + (vertex.x - center.x) * multiplier;
    vertex.y = center.y + (vertex.y - center.y) * multiplier;
  }
}

void Rectangle::rotate(const double degrees)
{
  double radians = degrees * M_PI / 180;
  const double xc = getCenter().x;
  const double yc = getCenter().y;
  for (auto & vertex : vertices_) {
    const double x = vertex.x;
    const double y = vertex.y;
    vertex.x = xc + (x - xc) * cos(radians) - (y - yc) * sin(radians);
    vertex.y = yc + (x - xc) * sin(radians) + (y - yc) * cos(radians);
  }
}

std::unique_ptr<Shape> Rectangle::getCopy() const
{
  return std::unique_ptr<Shape>(new Rectangle(*this));
}

void Rectangle::printInfo() const
{
  std::cout << "Rectangle:  ";
  std::cout << "  Width - " << calcDistance(vertices_[3], vertices_[0]) << ";";
  std::cout << "  Height - " << calcDistance(vertices_[1], vertices_[0]) << ";";
  std::cout << "  Center - ";
  std::cout << "x = " << getCenter().x << ", y = " << getCenter().y << ";";
  std::cout << "  Area: " << getArea() << "    ";
  for (auto vertex : vertices_) {
    std::cout << "{" << vertex.x << ", " << vertex.y << "};  ";
  }
  std::cout << std::endl;
}

double Rectangle::calcDistance(const point_t & p1, const point_t & p2) const
{
  return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

point_t Rectangle::getCenter() const
{
  return {(vertices_[0].x + vertices_[2].x) / 2, (vertices_[0].y + vertices_[2].y) / 2};
}
