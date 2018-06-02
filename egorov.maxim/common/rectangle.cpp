#include "rectangle.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace egorov;

Rectangle::Rectangle(const rectangle_t &rectangle) :
  rectangle_(rectangle),
  points_ {{rectangle_.pos.x - rectangle_.width / 2, rectangle_.pos.y + rectangle_.height / 2},
  {rectangle_.pos.x + rectangle_.width / 2, rectangle_.pos.y + rectangle_.height / 2},
  {rectangle_.pos.x - rectangle_.width / 2, rectangle_.pos.y - rectangle_.height / 2},
  {rectangle_.pos.x + rectangle_.width / 2, rectangle_.pos.y - rectangle_.height / 2}}

{
  if (rectangle_.height < 0.0 || rectangle_.width < 0.0)
  {
    throw std::invalid_argument("invalid_input");
  }
}

double Rectangle::getArea() const noexcept
{
  return rectangle_.width * rectangle_.height;
}

rectangle_t Rectangle::getFrameRect() const noexcept
{
  point_t top_left = rectangle_.pos;
  point_t bottom_right = rectangle_.pos;

  for (size_t i = 0; i < 4; i++)
 {
   if (points_[i].x < top_left.x)
   {
     top_left.x = points_[i].x;
   }

   if (points_[i].y > top_left.y)
   {
     top_left.y = points_[i].y;
   }

   if (points_[i].x > bottom_right.x)
   {
     bottom_right.x = points_[i].x;
   }

   if (points_[i].y < bottom_right.y)
   {
     bottom_right.y = points_[i].y;
   }
 }

 return {bottom_right.x - top_left.x, top_left.y - bottom_right.y, {rectangle_.pos}};
}

void Rectangle::move(const point_t &point) noexcept
{
  move(point.x - rectangle_.pos.x, point.y - rectangle_.pos.y);
}

void Rectangle::move(const double deltaX, const double deltaY) noexcept
{
  rectangle_.pos.x += deltaX;
  rectangle_.pos.y += deltaY;

  for (size_t i = 0; i < 4; i++)
  {
    points_[i].x += deltaX;
    points_[i].y += deltaY;
  }
}

void Rectangle::scale(const double coefficent)
{
  if (coefficent < 0.0 )
  {
    throw std::invalid_argument("invalid_coefficent");
  }
  rectangle_.height *= coefficent;
  rectangle_.width *= coefficent;

  for (size_t i = 0; i < 4; i++)
 {
   points_[i] = {rectangle_.pos.x + coefficent * (points_[i].x - rectangle_.pos.x),
   rectangle_.pos.y + coefficent * (points_[i].y - rectangle_.pos.y)};
 }
}

void Rectangle::rotate(double angle) noexcept
{
  angle = angle * M_PI / 180;

  double cosA = cos(angle);
  double sinA = sin(angle);

  for (size_t i = 0; i < 4; i++)
  {
    points_[i] = {rectangle_.pos.x + cosA * (points_[i].x - rectangle_.pos.x) - sinA * (points_[i].y - rectangle_.pos.y),
    rectangle_.pos.y + cosA * (points_[i].y - rectangle_.pos.y) + sinA * (points_[i].x - rectangle_.pos.x)};
  }

}

std::string Rectangle::getName() const noexcept
{
  return "Rectangle";
}
