#include "rectangle.hpp"

#include <stdexcept>
#include <iostream>
#include <cmath>

using namespace ponomarev;

Rectangle::Rectangle(const point_t &center, const double width, const double height):
  corners_{{center.x - width / 2.0, center.y + height / 2.0},
    {center.x + width / 2.0, center.y + height /2.0},
    {center.x + width / 2.0, center.y - height / 2.0},
    {center.x - width / 2.0, center.y - height /2.0}},
  width_(width),
  height_(height)
{
  if (width < 0.0 || height < 0.0)
  {
    throw std::invalid_argument("Invalid_input");
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  point_t center = {(corners_[0].x + corners_[2].x) / 2, (corners_[0].y + corners_[2].y) / 2};

  point_t top_left = center;
  point_t bottom_right = center;

  for (size_t i = 0; i < 4; i ++)
  {
    if (corners_[i].x < top_left.x)
    {
      top_left.x = corners_[i].x;
    }

    if (corners_[i].y > top_left.y)
    {
      top_left.y = corners_[i].y;
    }

    if (corners_[i].x > bottom_right.x)
    {
      bottom_right.x = corners_[i].x;
    }

    if (corners_[i].y < bottom_right.y)
    {
      bottom_right.y = corners_[i].y;
    }
  }

  return {bottom_right.x - top_left.x, top_left.y - bottom_right.y, center};
}

void Rectangle::move(const point_t &center)
{
  point_t point = getFrameRect().pos;
  move(center.x - point.x, center.y - point.y);
}

void Rectangle::move(const double dx, const double dy)
{
  for (size_t i = 0; i < 4; ++i)
  {
    corners_[i].x += dx;
    corners_[i].y += dy;
  }
}

void Rectangle::scale(const double coefficient)
{
  if (coefficient < 0.0)
  {
    throw std::invalid_argument("invalid scaling coefficient");
  }
  width_ *= coefficient;
  height_ *= coefficient;
}

void Rectangle::rotate(const double angle)
{
  double msin = sin(angle * M_PI / 180);
  double mcos = cos(angle * M_PI / 180);

  point_t center = getFrameRect().pos;
  for (size_t i = 0; i < 4; i++)
  {
    corners_[i] = {center.x + (corners_[i].x - center.x) * mcos - (corners_[i].y - center.y) * msin,
      center.y + (corners_[i].y - center.y) * mcos + (corners_[i].x - center.x) * msin};
  }
}

void Rectangle::printShape() const
{
  std::cout << "Rectangle";
}
