//
//  rectangle.cpp
//  A1
//
//  Created by Георгий Тимошенский on 12.03.2018.
//  Copyright © 2018 Георгий Тимошенский. All rights reserved.
//
#include "rectangle.hpp"
#include <iostream>
#include <cassert>

Rectangle::Rectangle(const point_t &pos, const double rectangle_width,const double rectangle_height):
  pos_(pos),
  width_(rectangle_width),
  height_(rectangle_height)
{
  assert(rectangle_width >= 0 && rectangle_height >= 0);
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  rectangle_t rectangle = {width_, height_, pos_};
  return rectangle;
}

point_t Rectangle::move( const double  dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
  return{ pos_.x, pos_.y };
}

point_t Rectangle::move(const point_t &posit)
{
  pos_.x = posit.x;
  pos_.y = posit.y;
  return {pos_.x, pos_.y};
}

void Rectangle::printInformation() const
{
  std::cout
  << "Width: " << width_ << "\n"
  << "Height: " << height_<< "\n"
  << "Center: "<< "(" << getFrameRect().pos.x << ","
  << getFrameRect().pos.y << ")" << "\n"
  << "Area: " << getArea() << "\n";
  
  std::cout
  << "Rectangle around rectangle: " << "\n"
  << "Height: " << getFrameRect().height << "\n"
  << "Width: " << getFrameRect().width << "\n"
  << "Center: "<< "(" << getFrameRect().pos.x << ","
  << getFrameRect().pos.y << ")" << "\n"
  << "________________________" << "\n";
}

