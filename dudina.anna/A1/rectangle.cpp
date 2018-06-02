#include "rectangle.hpp"

Rectangle::Rectangle(const point_t & pos, const double width, const double height) :
  pos_(pos),
  width_(width),
  height_(height)
{
  if (height <= 0) 
  { 
    height_ = 0;
    std::cerr << "Height must be >0 " << std::endl;
  }
  if (width <= 0) 
  {
    width_ = 0;
    std::cerr << "Widht must be >0 " << std::endl;
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return { height_,width_,{ pos_.x,pos_.y} };
}

void Rectangle::move(const point_t & pos)
{
  pos_= pos;
}

void Rectangle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void Rectangle::printInformation()
{
  std::cout << "Height of rectangle: " << height_ << std::endl;
  std::cout << "Width of rectangle: " << width_ << std::endl;
  std::cout << "Center of rectangle: {" << pos_.x << "," << pos_.y << "}" << std::endl;
}

