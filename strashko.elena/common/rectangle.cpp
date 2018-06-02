#include "rectangle.hpp"

#include <iostream>
#include <stdexcept>
#include <cmath>

strashko::Rectangle::Rectangle(const strashko::point_t &centre, double width, double height) :
  width_(width),
  height_(height),
  angle_(0.0)
{
  centre_ = centre;
  if (width_ < 0.0) {
    throw std::invalid_argument("Wrong width!");
  }
  if (height_ < 0.0) {
    throw std::invalid_argument("Wrong height!");
  }
}

double strashko::Rectangle::getArea() const noexcept
{
  return width_ * height_;
}

strashko::rectangle_t strashko::Rectangle::getFrameRect() const noexcept
{
  const double sine = sin(angle_ * M_PI / 180);
  const double cosine = cos(angle_ * M_PI / 180);
  const double width = height_ * fabs(sine) + width_ * fabs(cosine);
  const double height = height_ * fabs(cosine) + width_ * fabs(sine);
  return {centre_, width, height};
}

void strashko::Rectangle::move(const double dx, const double dy) noexcept
{
  centre_.x += dx;
  centre_.y += dy;
}

void strashko::Rectangle::move(const strashko::point_t &newcentre) noexcept
{
  centre_ = newcentre;
}

void strashko::Rectangle::scale(const double factor)
{
  if (factor < 0.0) {
    throw std::invalid_argument("Wrong factor!");
  }
  width_ *= factor;
  height_ *= factor;
}

void strashko::Rectangle::rotate(const double angle) noexcept
{
  angle_ += angle;
  if (angle_ >= 360.0) {
    angle_ = fmod(angle_, 360.0);
  }
}

std::unique_ptr<strashko::Shape> strashko::Rectangle::getCopy() const noexcept
{
  return std::unique_ptr<strashko::Shape>(new Rectangle(*this));
}

void strashko::Rectangle::printInfo() const
{
  std::cout << "Rectangle:  ";
  std::cout << "  Width - " << width_<< ";";
  std::cout << "  Height - " << height_ << ";";
  double x = (width_/2);
  double y = (height_/2);
  std::cout << "  Center - ";
  std::cout << "x = " << x << ", y = " << y << ";";
  std::cout << "  Area: " << getArea() << "    ";
}
