#include <iostream>
#include <stdexcept>
#include "rectangle.hpp"

Rectangle::Rectangle(double width, double height, const point_t &center_point):
  w_(width),
  h_(height),
  rectangle_center_(center_point)
{
  if ((width < 0.0) || (height < 0.0))
  {
    throw std::invalid_argument("Parameters can't be lower thatn 0");
  }
}
double Rectangle::getArea() const
{
  return (h_*w_);
}
void Rectangle::getInfo() const
{
  std::cout << std::endl << "h: "<<h_<<"\t"<<"w: " << w_ << std::endl;
  std::cout << "Area: " << getArea() << std::endl;
  std::cout << "Point(x, y): (" << rectangle_center_.x << ", " << rectangle_center_.y << ")" << std::endl;
  std::cout << "Frame rectangle(h,w,center(x,y)): " << getFrameRect().height << ", " << getFrameRect().width
      << ", (" << getFrameRect().pos.x << ", " << getFrameRect().pos.y << ")" << std::endl;
}
rectangle_t Rectangle::getFrameRect() const
{
  return{w_, h_, rectangle_center_};
}
void Rectangle::move(const double dx, const double dy)
{
  rectangle_center_.x += dx;
  rectangle_center_.y += dy;
}
void Rectangle::move(const point_t &point)
{
  rectangle_center_ = point;
}
