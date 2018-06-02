#include "rectangle.hpp"
#include <iostream>
#include <cmath>

vasekha::Rectangle::Rectangle(const vasekha::point_t & pos, const double width, const double height):
  pos_(pos),
  width_(width),
  height_(height),
  angle_(0.0)
{
  if(width<0.0 || height<0.0)
  {
    throw std::invalid_argument("Invalid width or height");
  }
}

double vasekha::Rectangle::getArea() const noexcept
{
  return width_*height_;
}

vasekha::rectangle_t vasekha::Rectangle::getFrameRect() const noexcept
{
  const double angle_rad = (angle_*M_PI)/180.0;
  return {pos_, width_*abs(cos(angle_rad))+height_*abs(sin(angle_rad)), height_
    *abs(cos(angle_rad))+width_*abs(sin(angle_rad))};
}

void vasekha::Rectangle::move(const vasekha::point_t & point) noexcept
{
  pos_=point;
}

void vasekha::Rectangle::move(const double dx, const double dy) noexcept
{
  pos_.x+=dx;
  pos_.y+=dy;
}

void vasekha::Rectangle::scale(const double factor)
{
  if(factor<0.0)
  {
    throw std::invalid_argument("Invalid factor");
  }
  width_*=factor;
  height_*=factor;
}

void vasekha::Rectangle::rotate(const double angle) noexcept
{
  angle_=std::fmod(angle_+angle,360);
}

void vasekha::Rectangle::print(std::ostream & out) const noexcept
{
  out << "Rectangle: center: (" << pos_.x << "," << pos_.y << "), width = "
    << width_ << ", height = " << height_  << ", angle = " << angle_ << std::endl;
}
