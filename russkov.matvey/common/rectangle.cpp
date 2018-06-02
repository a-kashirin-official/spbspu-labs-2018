//
// Created by russk on 31.03.2018.
//
#include <iostream>
#include <stdexcept>
#include <cmath>
#include "rectangle.hpp"
#include "base-types.hpp"

russkov::Rectangle::Rectangle(point_t &center, double width, double height):
  center_(center),
  width_(width),
  height_(height),
  alpha_(0.0)
{
  if ((width_ < 0.0) || (height_ < 0.0))
  {
    throw std::invalid_argument("width and height must be non-negative");
  }
}

double russkov::Rectangle::getArea() const
{
  return width_*height_ ;
}

russkov::rectangle_t russkov::Rectangle::getFrameRect() const
{
  return rectangle_t{width_, height_, center_};
}

void russkov::Rectangle::move(const point_t &point)
{
  center_ = point;
}

void russkov::Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void russkov::Rectangle::scale(const double ratio)
{
  if (ratio < 0.0)
  {
    throw std::invalid_argument("coefficient should be not negative");
  }
  width_ *= ratio;
  height_ *= ratio;
}

void russkov::Rectangle::rotate(const double alpha)
{
  alpha_ += alpha;
  if (alpha_ >= 360.0)
  {
    alpha_ = fmod(alpha_, 360.0);
  }
}
