#include "rectangle.hpp"

Rectangle::Rectangle(double width, double height, const point_t& rect) :
  w_(width),
  h_(height), 
  center_(rect)
{}

double Rectangle::getWidth() const
{
  return w_;
}
double Rectangle::getHeight() const
{
  return h_;
}
double Rectangle::getArea() const
{
  return(w_ * h_);
}
rectangle_t Rectangle::getFrameRect() const
{
  return{w_, h_, center_};
}

void Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Rectangle::move(const point_t & center)
{
  center_ = center;
}

void Rectangle::print() const
{
  std::cout << "Rectangle info: " << std::endl;
  std::cout << "center: " << center_.x << " " << center_.y << std::endl;
}
