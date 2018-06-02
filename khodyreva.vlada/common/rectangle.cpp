#include "rectangle.hpp"
#include <stdexcept>
#include <cmath>

using namespace khodyreva;

Rectangle::Rectangle(const point_t & pos, const double height, const double width):
  width_(width),
  height_(height),
  pos_(pos),
  vertex_{{pos.x - width / 2, pos.y - height / 2}, // left bottom vertex
          {pos.x - width / 2, pos.y + height / 2}, // left top vertex
          {pos.x + width / 2, pos.y + height / 2}, // right top vertex
          {pos.x + width / 2, pos.y - height / 2}} // right bottom vertex

{
  if ((height_ < 0.0)||(width_ < 0.0))
  {
    throw std::invalid_argument("Wrong input data");
  }
}

double Rectangle::getArea() const 
{
  return height_*width_;
}

rectangle_t Rectangle::getFrameRect() const
{
  double right = vertex_[0].x;
  double left = vertex_[0].x;
  double top = vertex_[0].y;
  double bottom = vertex_[0].y;
  for (int i =1; i < 4; i++)
  {
    if (vertex_[i].x > right)
    {
      right = vertex_[i].x;
    }
    if (vertex_[i].x < left)
    {
      left = vertex_[i].x;
    }
    if (vertex_[i].y > top)
    {
      top = vertex_[i].y;
    }
    if (vertex_[i].y < bottom)
    {
      bottom = vertex_[i].y;
    }
  }
  return {{((right + left) / 2), ((top + bottom) / 2)}, (top - bottom), (right - left)};
}

void Rectangle::move(const point_t &pos)
{
  for (int i = 0; i < 4; i++)
  {
    vertex_[i].x += pos.x - pos_.x;
    vertex_[i].y += pos.y - pos_.y;
  }
  pos_ = pos;
}

void Rectangle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
  for (int i = 0; i < 4; i++)
  {
    vertex_[i].x += dx;
    vertex_[i].y += dy;
  }
}

void Rectangle::scale(const double ratio)
{
  if (ratio <= 0.0)
  {
    throw std::invalid_argument("Wrong input data, ratio must be greater than 0");
  }
  height_ *= ratio;
  width_ *= ratio;
  vertex_[0] = {pos_.x + width_ / 2, pos_.y + height_ / 2};
  vertex_[1] = {pos_.x - width_ / 2, pos_.y + height_ / 2};
  vertex_[2] = {pos_.x - width_ / 2, pos_.y - height_ / 2};
  vertex_[3] = {pos_.x + width_ / 2, pos_.y - height_ / 2};
}

void Rectangle::rotate(double angle)
{
  double sinA = sin(angle * M_PI / 180);
  double cosA= cos(angle * M_PI / 180);
  point_t center = getFrameRect().pos;
  for (int i = 0; i < 4; i++)
  {
    vertex_[i] = {center.x + (vertex_[i].x - center.x) * cosA
        - (vertex_[i].y - center.y) * sinA, center.y + (vertex_[i].x - center.x) * sinA
        + (vertex_[i].y - center.y) * cosA};
  }
}


std::string Rectangle::getName() const
{
  return "Rectangle";
}
