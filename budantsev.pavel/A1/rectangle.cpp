#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const double width, const double height,const point_t &poss)
{
  if (width < 0.0 || height < 0.0) 
  {
    throw std::invalid_argument("Height and width must be nonnegative");
  }
  else
 
  width_=width;
  height_=height;
  center_=poss;
}

double Rectangle::getArea() const
{
  return width_ * height_;
};

rectangle_t Rectangle::getFrameRect() const
{
  return {height_,width_, {center_.x,center_.y}};
};

void Rectangle::move(const point_t &poss)
{
  center_ = poss;
};

void Rectangle::move(const double Ox, const double Oy)
{
  center_.x += Ox;
  center_.y += Oy;
};

void Rectangle::info() const
{
  std::cout<< "Width: " << width_ << " Height: " << height_;
  std::cout<<" Center: "<< "x = " << center_.x << " y = " << center_.y <<  std::endl;
};

