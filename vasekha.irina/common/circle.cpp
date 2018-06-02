#include "circle.hpp"
#include <iostream>
#include <cmath>

vasekha::Circle::Circle(const vasekha::point_t & pos, const double radius):
  pos_(pos),
  radius_(radius)
{
  if(radius<0.0)
  {
    throw std::invalid_argument("Invalid radius");
  }
}

double vasekha::Circle::getArea() const noexcept
{
  return M_PI*radius_*radius_;
}

vasekha::rectangle_t vasekha::Circle::getFrameRect() const noexcept
{
  return {pos_, 2.0*radius_, 2.0*radius_};
}

void vasekha::Circle::move(const vasekha::point_t & point) noexcept
{
  pos_=point;
}

void vasekha::Circle::move(const double dx, const double dy) noexcept
{
  pos_.x+=dx;
  pos_.y+=dy;
}

void vasekha::Circle::scale(const double factor)
{
  if(factor<0.0)
  {
    throw std::invalid_argument("Invalid factor");
  }
  radius_*=factor;
}

void vasekha::Circle::rotate(const double /*angle*/) noexcept
{}

void vasekha::Circle::print(std::ostream & out) const noexcept
{
  out << "Circle: center: (" << pos_.x << "," << pos_.y << "), radius=" 
    << radius_ << std::endl;
}
