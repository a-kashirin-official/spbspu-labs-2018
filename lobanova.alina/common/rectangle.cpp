#include "rectangle.hpp"
#include <stdexcept>
#include <limits>
#include <iostream>

using namespace lobanova;

lobanova::Rectangle::Rectangle(const point_t &centre, const double width, const double height) :
    centre_(centre),
    width_(width),
    height_(height),
    angle_(0)
{
  if (width <= 0) {
    throw std::invalid_argument("Width is incorrect. Must be positive.");
  }
  if (height <= 0) {
    throw std::invalid_argument("Height is incorrect. Must be positive.");
  }
}

lobanova::rectangle_t lobanova::Rectangle::getFrameRect() const
{
  point_t c = centre_;
  point_t a = {0, 0};
  double maxx = -std::numeric_limits<double>::max(), maxy = -std::numeric_limits<double>::max();
  double minx = std::numeric_limits<double>::max(), miny = std::numeric_limits<double>::max();
  for (int i = -1; i <= 1; i += 2) {
    for (int j = -1; j <= 1; j += 2) {
      a = {(c.x + j * width_ / 2), (c.y + i * height_ / 2)};

      a.rotate(c, angle_);

      maxx = std::max(maxx, a.x);
      maxy = std::max(maxy, a.y);
      minx = std::min(minx, a.x);
      miny = std::min(miny, a.y);
    }
  }

  return {c, maxx - minx, maxy - miny};

}

double lobanova::Rectangle::getArea() const
{
  return width_ * height_;
}

void lobanova::Rectangle::move(const point_t &a)
{
  centre_ = a;
}

void lobanova::Rectangle::move(const double dx, const double dy)
{
  centre_.x += dx;
  centre_.y += dy;
}

void lobanova::Rectangle::scale(const double p)
{
  if (p <= 0) {
    throw std::invalid_argument("Invalid parameter!");
  }

  width_ *= p;
  height_ *= p;
}

double lobanova::Rectangle::getWidth() const
{
  return width_;
}

double lobanova::Rectangle::getHeight() const
{
  return height_;
}

point_t lobanova::Rectangle::getCentre() const
{
  return centre_;
}

void Rectangle::rotate(double p)
{
  angle_ += p;
}

void Rectangle::rotatePoint(const point_t &a, double p)
{
  angle_ += p;
  centre_.rotate(a, p);
}
