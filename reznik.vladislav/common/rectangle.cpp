#include "rectangle.hpp"
#include  <stdexcept>


reznik::Rectangle:: Rectangle(double width,double height, const reznik::point_t& rec):
  width_(width),
  height_(height),
  rec_(rec)
{
  if(width_ < 0 || height_ < 0)
  {
    throw std:: invalid_argument("Wrong parametrs");
  }
}
double reznik::Rectangle::getArea() const
{
  return(width_ *height_);
}
reznik::rectangle_t reznik::Rectangle::getFrameRect() const
{
  return{ width_,height_,rec_};
}
void reznik::Rectangle::move(double dx,double dy)
{
  rec_.x += dx;
  rec_.y += dy;
}
void reznik::Rectangle::move(const reznik::point_t& center)
{
  rec_ = center;
}

void reznik::Rectangle::scale(double k)
{
  if (k < 0)
  {
    throw std:: invalid_argument("Wrong parametrs");
  }
  else
  {
    width_ *= k;
    height_ *= k;
  }
}
