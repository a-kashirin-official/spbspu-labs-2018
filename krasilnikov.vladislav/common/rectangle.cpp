#include "rectangle.hpp"

#include <iostream>
#include <stdexcept>
#include <math.h>

using namespace krasilnikov;

krasilnikov::Rectangle::Rectangle(const double height, const double width, const point_t & middle):
  middle_(middle),
  height_(height),
  width_(width),
  angle_(0.0)
{
  if (height_ < 0.0)
  {
    throw std::invalid_argument("Incorrect height value");
  }
  if (width_ < 0.0)
  {
    throw std::invalid_argument("Incorrect width value");
  }
}

double krasilnikov::Rectangle::getArea() const
{
  return height_ * width_;
}

rectangle_t krasilnikov::Rectangle::getFrameRect() const
{
  const double sine = sin(angle_ * M_PI / 180);
  const double cosine = cos(angle_ * M_PI / 180);
  const double height = height_ * abs(cosine) + width_ * abs(sine);
  const double width = width_ * abs(cosine) + height_ * abs(sine);
  return {height, width, middle_};
}

void krasilnikov::Rectangle::move(const point_t & newPosition)
{
  middle_ = newPosition;
}

void krasilnikov::Rectangle::move(const double dx, const double dy)
{
  middle_.x += dx;
  middle_.y += dy;
}

point_t krasilnikov::Rectangle::getPosition() const
{
  return middle_;
}

double krasilnikov::Rectangle::getHeight() const
{
  return height_;
}

double krasilnikov::Rectangle::getWidth() const
{
  return width_;
}

void krasilnikov::Rectangle::scale(const double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Invalid factor");
  }
  height_ *= factor;
  width_ *= factor;
}

void krasilnikov::Rectangle::rotate(const double angle)
{
  angle_ += angle;
  if (angle_ >= 360)
  {
    angle_ = fmod(angle_, 360.0);
  }
}
