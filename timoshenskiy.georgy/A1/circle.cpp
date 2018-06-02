//
//  circle.cpp
//  A1
//
//  Created by Георгий Тимошенский on 12.03.2018.
//  Copyright © 2018 Георгий Тимошенский. All rights reserved.
//
#include <iostream>
#include "circle.hpp"
#include "base-types.hpp"
#include <cmath>
#include <cassert>

Circle::Circle(const point_t &pos ,const double circle_radius):
  pos_(pos),
  radius_(circle_radius)
{
  assert(circle_radius >= 0);
}

double Circle::getArea() const
{
  return radius_ * radius_ * M_PI;
}

rectangle_t Circle::getFrameRect() const
{
  rectangle_t rectangle {2 * radius_, 2 * radius_, pos_};
  return rectangle;
}

point_t Circle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
  return {pos_.x, pos_.y};
}

point_t Circle::move( const point_t &position)
{
  pos_.x = position.x;
  pos_.y =position.y;
  return {pos_.x, pos_.y};
}
void Circle::printInformation() const
{
  std::cout
  << "Radius: " << radius_ << "\n"
  << "Center: "<< "(" << getFrameRect().pos.x << ","
  << getFrameRect().pos.y << ")" << "\n"
  << "Area: " << getArea() << "\n";

  std::cout
  << "Rectangle around circle: " << "\n"
  << "Height: " << getFrameRect().height << "\n"
  << "Width: " << getFrameRect().width << "\n"
  << "Center: "<< "(" << getFrameRect().pos.x << ","
  << getFrameRect().pos.y << ")" << "\n"
  << "________________________" << "\n";
}

