#include "rectangle.hpp"
#include <iostream>
#include <cmath>

shalgueva::Rectangle::Rectangle(const rectangle_t & rect):
  rect_{rect},
  angle_(0)
{
  if ((rect_.width < 0.0)||(rect_.height < 0.0))
  {
    throw std::invalid_argument("Error. Invalid height or width");
  }
  corner_[0] = {rect_.pos.x - rect_.width /2, rect_.pos.y - rect_.height / 2}; //left bottom
  corner_[1] = {rect_.pos.x - rect_.width /2, rect_.pos.y + rect_.height / 2}; //left top
  corner_[2] = {rect_.pos.x + rect_.width /2, rect_.pos.y + rect_.height / 2}; //right top
  corner_[3] = {rect_.pos.x + rect_.width /2, rect_.pos.y - rect_.height / 2}; //right bottom
}

double shalgueva::Rectangle::getArea() const noexcept
{
  return rect_.width * rect_.height;
}

shalgueva::rectangle_t shalgueva::Rectangle::getFrameRect() const noexcept
{
  double maxY = std::max(std::max(corner_[0].y, corner_[1].y),
    std::max(corner_[2].y, corner_[3].y));
  double maxX = std::max(std::max(corner_[0].x, corner_[1].x),
    std::max(corner_[2].x, corner_[3].x));
  double minY = std::min(std::min(corner_[0].y, corner_[1].y),
    std::max(corner_[2].y, corner_[3].y));
  double minX = std::min(std::min(corner_[0].x, corner_[1].x),
    std::max(corner_[2].x, corner_[3].x));
  return { (maxX - minX), (maxY - minY), { (minX + maxX) / 2, (minY + maxY) / 2 } };
}

void shalgueva::Rectangle::move(double dx, double dy) noexcept
{
  rect_.pos = { rect_.pos.x + dx, rect_.pos.y + dy };
  for (size_t i = 0; i < 4; i++)
  {
    corner_[i].x += dx;
    corner_[i].y += dy;
  }
}

void shalgueva::Rectangle::move(const point_t & posTo) noexcept
{
  for (size_t i = 0; i < 4; i++)
  {
    corner_[i].x += posTo.x - rect_.pos.x;
    corner_[i].y += posTo.y - rect_.pos.y;
  }
  rect_.pos = posTo;
}

void shalgueva::Rectangle::scale(double coefficient)
{
  if (coefficient < 0.0)
  {
    throw std::invalid_argument("Error. Invalid parameter of scaling");
  }
  for (size_t i = 0; i < 4; i++)
  {
    corner_[i].x = (corner_[i].x - rect_.pos.x) * coefficient + rect_.pos.x;
    corner_[i].y = (corner_[i].y - rect_.pos.y) * coefficient + rect_.pos.y;
  }
  rect_.height *= coefficient;
  rect_.width *= coefficient;
}

void shalgueva::Rectangle::rotate(double alpha) noexcept
{
  double sinAlpha = sin(alpha * 3.14 / 180);
  double cosAlpha = cos(alpha * 3.14 / 180);
  shalgueva::point_t center = getFrameRect().pos;
  for (size_t i =0; i < 4; i++)
  {
    corner_[i].x = center.x + (corner_[i].x - center.x) * cosAlpha - (corner_[i].y - center.y) * sinAlpha;
    corner_[i].y = center.y + (corner_[i].y - center.y) * cosAlpha + (corner_[i].x - center.x) * sinAlpha;
  }
}


