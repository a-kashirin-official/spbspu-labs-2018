#include "rectangle.hpp"

Rectangle:: Rectangle(double width,double height, const point_t& rec):
  width_(width),
  height_(height),
  rec_(rec)
{
  if(width_ <= 0 || height_ <= 0)
  {
    throw std:: invalid_argument("Wrong parametrs");
  }
}
double Rectangle::getArea() const
{
  return(width_ *height_);
}
rectangle_t Rectangle::getFrameRect() const
{
  return{ width_,height_,rec_};
}
void Rectangle::move(double dx,double dy)
{
  rec_.x += dx;
  rec_.y += dy;
}
void Rectangle::move(const point_t& center)
{
  rec_ = center;
}
