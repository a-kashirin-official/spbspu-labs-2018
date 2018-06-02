
#include "rectangle.hpp"
#include <stdexcept>
#define _USE_MATH_DEFINES
#include <math.h>

zhukova::Rectangle::Rectangle(const zhukova::point_t & center, double width, double height, double angle):
  center_(center),
  width_(width),
  height_(height),
  angle_(angle)
{
  if (width <= 0) {
    throw std::invalid_argument("Rectangle: Invalid width value, constructor");
  }
  if (height <= 0) {
    throw std::invalid_argument("Rectangle: Invalid height value, constructor");
  }
}

zhukova::Rectangle::Rectangle(const Rectangle & arg):
  center_(arg.center_),
  width_(arg.width_),
  height_(arg.height_),
  angle_(arg.angle_)
{
  if (arg.width_ <= 0) {
    throw std::invalid_argument("Rectangle: Invalid width value, copy constructor");
  }
  if (arg.height_ <= 0) {
    throw std::invalid_argument("Rectangle: Invalid height value, copy constructor");
  }
}

double zhukova::Rectangle::getArea() const
{
  return width_ * height_;
}

zhukova::rectangle_t zhukova::Rectangle::getFrameRect() const
{
  point_t init1 = { width_ / 2, height_ / 2 };
  point_t init2 = { width_ / 2, - height_ / 2 };
  double rad = (M_PI / 180) * angle_;
  point_t newPoint1 = {0, 0};
  point_t newPoint2 = {0, 0};

  newPoint1.x = abs( init1.x * cos(rad) - init1.y * sin(rad) );
  newPoint1.y = abs( init1.y * cos(rad) + init1.x * sin(rad) );

  newPoint2.x = abs( init2.x * cos(rad) - init2.y * sin(rad) );
  newPoint2.y = abs( init2.y * cos(rad) + init2.x * sin(rad) );

  return zhukova::rectangle_t{ ( newPoint1.x > newPoint2.x ? newPoint1.x : newPoint2.x ) * 2,
      ( newPoint1.y > newPoint2.y ? newPoint1.y : newPoint2.y ) * 2 , center_ };
}

void zhukova::Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void zhukova::Rectangle::move(const zhukova::point_t & point)
{
  center_ = point;
}

void zhukova::Rectangle::scale(double coefficient)
{
  if (coefficient < 0) {
    throw std::invalid_argument("Rectangle: Invalid scaling factor");
  }
  width_ *= coefficient;
  height_ *= coefficient;
}

void zhukova::Rectangle::rotate(double deg)
{
  angle_ += deg;
}
