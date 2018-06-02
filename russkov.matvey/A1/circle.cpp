//
// Created by russk on 31.03.2018.
//

#include <cmath>
#include <iostream>
#include <stdexcept>
#include "circle.hpp"
#include "base-types.hpp"

Circle::Circle(const point_t &center, double radius):
  center_(center),
  radius_(radius)
{
  if (radius_ < 0.0)
  {
    throw std::invalid_argument("radius must be non-negative");
  }
}

double Circle::getArea() const
{
  return  M_PI*radius_*radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{2*radius_, 2*radius_, center_};
}

void Circle::move(const point_t &point)
{
  center_ = point;
}

void Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Circle::scale(const double ratio)
{
  if (ratio <= 0.0)
  {
    throw std::invalid_argument("coefficient should be positive");
  }
  radius_ *= ratio;
}

