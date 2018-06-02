#include "circle.hpp"
#include <stdexcept>
#include <cmath>

using namespace lobanova;

lobanova::Circle::Circle(const point_t &centre, const double rad) : centre_(centre), rad_(rad), angle_(0)
{
  if (rad <= 0) {
    throw std::invalid_argument("Radius is incorrect. Must be positive.");
  }
}

rectangle_t lobanova::Circle::getFrameRect() const
{
  return {centre_, rad_ * 2, rad_ * 2};
}

double lobanova::Circle::getArea() const
{
  return rad_ * rad_ * M_PI;
}

void lobanova::Circle::move(const point_t &a)
{
  centre_ = a;
}

void lobanova::Circle::move(const double dx, const double dy)
{
  centre_.x += dx;
  centre_.y += dy;
}

double lobanova::Circle::getRadius() const
{
  return rad_;
}

void lobanova::Circle::scale(const double p)
{
  if (p <= 0) {
    throw std::invalid_argument("Incorrect parameter!");
  }
  rad_ *= p;
}

void Circle::rotatePoint(const point_t &a, double p)
{
  centre_.rotate(a, p);
}

void Circle::rotate(double p)
{
  angle_ += p;
}

