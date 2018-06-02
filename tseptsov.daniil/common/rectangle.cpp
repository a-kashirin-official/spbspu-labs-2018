#include <iostream>
#include <cmath>
#include "rectangle.hpp"

using namespace tseptsov;

Rectangle::Rectangle(const double width, const double height, const point_t &pos) :
  vertexes_{{pos.x - width / 2, pos.y - height / 2},
            {pos.x - width / 2, pos.y + height / 2},
            {pos.x + width / 2, pos.y + height / 2},
            {pos.x + width / 2, pos.y - height / 2}}
{
  if (width < 0.0 || height < 0.0) {
    throw std::invalid_argument("Width and height of the rectangle must be > 0");
  }
}

double Rectangle::getArea() const
{
  return getDistance(vertexes_[3], vertexes_[0]) * getDistance(vertexes_[1], vertexes_[0]);
}

rectangle_t Rectangle::getFrameRect() const
{
  double MaxX = vertexes_[0].x;
  double MaxY = vertexes_[0].y;
  double MinX = vertexes_[0].x;
  double MinY = vertexes_[0].y;

  for (auto vertex : vertexes_) {
    MaxX = (vertex.x > MaxX) ? vertex.x : MaxX;
    MinX = (vertex.x < MinX) ? vertex.x : MinX;
    MaxY = (vertex.y > MaxY) ? vertex.y : MaxY;
    MinY = (vertex.y < MinY) ? vertex.y : MinY;
  }
  return {MaxX - MinX, MaxY - MinY, {MinX + (MaxX - MinX) / 2, MinY + (MaxY - MinY) / 2}};
}


void Rectangle::move(const point_t &newpos)
{
  move(newpos.x - getCenter().x, newpos.y - getCenter().y);
}


void Rectangle::move(const double dx, const double dy)
{
  for (auto &vertex : vertexes_) {
    vertex.x += dx;
    vertex.y += dy;
  }
}

void Rectangle::OutData() const
{
  std::cout << "Width: " << getDistance(vertexes_[3], vertexes_[0]) << std::endl;
  std::cout << "Height: " << getDistance(vertexes_[1], vertexes_[0]) << std::endl;
  std::cout << "Spot of middle on Ox = " << getCenter().x << std::endl;
  std::cout << "Spot of middle on Oy = " << getCenter().y << std::endl << std::endl;
}

void Rectangle::scale(double coef)
{
  if (coef < 0.0) {
    throw std::invalid_argument("ratio must be >= 0");
  }
  const point_t center = getCenter();
  for (auto &vertex : vertexes_) {
    vertex.x = center.x + (vertex.x - center.x) * coef;
    vertex.y = center.y + (vertex.y - center.y) * coef;
  }
}

void tseptsov::Rectangle::rotate(double deg)
{
  double deg_ = deg * M_PI / 180;
  double xc = (vertexes_[0].x + vertexes_[2].x) / 2;
  double yc = (vertexes_[0].y + vertexes_[2].y) / 2;
  for (auto &pos : vertexes_) {
    pos = {xc + (pos.x - xc) * cos(deg_) - (pos.y - yc) * sin(deg_),
           yc + (pos.y - yc) * cos(deg_) + (pos.x - xc) * sin(deg_)
    };
  }
}

double Rectangle::getDistance(const point_t &p1, const point_t &p2) const
{
  return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

point_t Rectangle::getCenter() const
{
  return {(vertexes_[0].x + vertexes_[2].x) / 2, (vertexes_[0].y + vertexes_[2].y) / 2};
}

