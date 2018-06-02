#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const point_t & pos, const double height, const double width):
  width_(width),
  height_(height),
  pos_(pos)
{
  if ((height_<0.0)||(width_<0.0))
  {
    std::cerr << "Wrong input data" << std::endl;
  }
}
double Rectangle::getArea() const 
{
  return height_*width_;
}
rectangle_t Rectangle::getFrameRect() const
{
  return{pos_,height_,width_};
}
void Rectangle::move(const point_t &pos)
{
  pos_=pos;
}
void Rectangle::move(const double dx, const double dy)
{
  pos_.x+=dx;
  pos_.y+=dy;
}


