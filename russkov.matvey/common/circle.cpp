//
// Created by russk on 31.03.2018.
//
#include <cmath>
#include <iostream>
#include <stdexcept>
#include "circle.hpp"
#include "base-types.hpp"

russkov::Circle:: Circle (const point_t &center, double radius):
  center_(center),
  radius_(radius),
  alpha_(0.0)
{
  if (radius < 0.0)
  {
    throw std::invalid_argument("radius must be non-negative");
  }
}

double russkov::Circle::getArea() const
{
  return  M_PI*radius_*radius_;
}

russkov::rectangle_t russkov::Circle::getFrameRect() const
{
  return rectangle_t{2*radius_, 2*radius_, center_};
}

void russkov::Circle::move(const point_t &point)
{
  center_ = point;
}

void russkov::Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void russkov::Circle::scale(const double ratio)
{
  if (ratio < 0.0)
  {
    throw std::invalid_argument("coefficient should be not negative");
  }
  radius_ *= ratio;
}

void russkov::Circle::rotate(const double alpha)
{
  alpha_ += alpha;
  if (alpha >= 360.0)
  {
    alpha_ = fmod(alpha_, 360.0);
  }
}

