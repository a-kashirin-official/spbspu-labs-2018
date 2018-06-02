#include "rectangle.hpp"

usov::Rectangle::Rectangle(double width, double height, const point_t& rect) :
  w_(width),
  h_(height), 
  center_(rect)
{
  if (w_ < 0.0)
  {
    throw std::invalid_argument("Width could be > 0.0");
  }
  if (h_ < 0.0)
  {
    throw std::invalid_argument("Width could be > 0.0");
  }
}

double usov::Rectangle::getWidth() const
{
  return w_;
}
double usov::Rectangle::getHeight() const
{
  return h_;
}
double usov::Rectangle::getArea() const
{
  return(w_ * h_);
}
usov::rectangle_t usov::Rectangle::getFrameRect() const
{
  return{w_, h_, center_};
}

void usov::Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void usov::Rectangle::move(const point_t & center)
{
  center_ = center;
}

void usov::Rectangle::scale(double dscale)
{
  if (dscale < 0.0)
  {
    throw std::invalid_argument("Scale could be > 0.0");
  }
  w_ *= dscale;
  h_ *= dscale;
}

void usov::Rectangle::print() const
{
  std::cout << "Rectangle info: " << std::endl;
  std::cout << "center: " << center_.x << " " << center_.y << std::endl;
  std::cout << "width: " << w_ << " height: " << h_ << std::endl;
  std::cout << std::endl;
}
