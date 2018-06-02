#include "rectangle.hpp"

#include <stdexcept>
#include <cmath>
#include <iostream>

sokolova::Rectangle::Rectangle(const sokolova::point_t &centre, double width, double height) :
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

double sokolova::Rectangle::getArea() const noexcept
{
  return width_ * height_;
}

sokolova::rectangle_t sokolova::Rectangle::getFrameRect() const noexcept
{
  const double sine = sin(angle_ * M_PI / 180);
  const double cosine = cos(angle_ * M_PI / 180);
  const double width = height_ * fabs(sine) + width_ * fabs(cosine);
  const double height = height_ * fabs(cosine) + width_ * fabs(sine);
  return {centre_, width, height};
}

void sokolova::Rectangle::move(const double dx, const double dy) noexcept
{
  centre_.x += dx;
  centre_.y += dy;
}

void sokolova::Rectangle::move(const sokolova::point_t &newcentre) noexcept
{
  centre_ = newcentre;
}

void sokolova::Rectangle::scale(const double factor)
{
  if (factor < 0.0) {
    throw std::invalid_argument("Wrong factor!");
  }
  width_ *= factor;
  height_ *= factor;
}

void sokolova::Rectangle::rotate(const double angle) noexcept
{
  angle_ += angle;
  if (angle_ >= 360.0) {
    angle_ = fmod(angle_, 360.0);
  }
}

std::unique_ptr<sokolova::Shape> sokolova::Rectangle::getCopy() const noexcept
{
  return std::unique_ptr<sokolova::Shape>(new Rectangle(*this));
}

void sokolova::Rectangle::printInfo() const
{
  std::cout << "Rectangle" << std::endl;
  std::cout << "Area: " << getArea() << std::endl;
  sokolova::rectangle_t rectangle = getFrameRect();
  std::cout << "Frame for object:" << std::endl;
  std::cout << "Centre: " << rectangle.pos.x << ", " << rectangle.pos.y << std::endl;
  std::cout << "Width: " << rectangle.width << std::endl;
  std::cout << "Height: " << rectangle.height << std::endl;
}
