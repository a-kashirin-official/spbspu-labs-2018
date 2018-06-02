//
//  circle.cpp
//  
//  Copyright © 2018 Георгий Тимошенский. All rights reserved.
//
#include "circle.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <cmath>

timoshenskiy::Circle::Circle(const point_t &pos, const double circle_radius):
  pos_(pos),
  radius_(circle_radius),
  angle_(0.0)
{
  if (circle_radius < 0.0)
  {
    throw std::invalid_argument("ERROR. Invalid radius of circle.");
  }
}

double timoshenskiy::Circle::getArea() const
{
  return radius_ * radius_ * M_PI;
}

timoshenskiy::rectangle_t timoshenskiy::Circle::getFrameRect() const
{
  rectangle_t rectangle {2*radius_, 2*radius_, pos_};
  return rectangle;
}

void timoshenskiy::Circle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void timoshenskiy::Circle::move( const point_t &position)
{
  pos_.x = position.x;
  pos_.y = position.y;
}

void timoshenskiy::Circle::scale(double multiplier)
{
  if (multiplier < 0.0)
  {
    throw std::invalid_argument ("ERROR. Multiplier shouldn't be negative");
  }
  else
  {
    radius_ *= multiplier;
  }
}

void timoshenskiy::Circle::rotate(double degrees)
{
  angle_ += degrees;
  if (angle_ >= 360)
  {
    angle_ = fmod(angle_, 360.0);
  }
}

std::string timoshenskiy::Circle::printInformation() const
{
  std::stringstream info;
  
  info << "\t Radius: " << radius_ << "\n"
  << "\t Center: "<< "(" << getFrameRect().pos.x << ","
  << getFrameRect().pos.y << ")" << "\n"
  << "\t Area: " << getArea() << "\n";
  
  info << "Rectangle around circle: " << "\n"
  << "\t Height: " << getFrameRect().height << "\n"
  << "\t Width: " << getFrameRect().width << "\n"
  << "\t Center: "<< "(" << getFrameRect().pos.x << ","
  << getFrameRect().pos.y << ")" << "\n"
  << "________________________" << "\n";
  
  return info.str();
}
