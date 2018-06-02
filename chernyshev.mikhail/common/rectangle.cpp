#include "rectangle.hpp"
#include <iostream>
#include <cassert>

using namespace chernyshev;

chernyshev::Rectangle::Rectangle(double h,double w,point_t c): height_(h),width_(w),center_(c)
{
  if (h<0.0)
  {
    throw std::invalid_argument("Hight must be >=0");
  }
  if (w<0.0)
  {
    throw std::invalid_argument("Width must be >=0");
  }
}

double chernyshev::Rectangle::getArea()const
{
  return height_*width_;
}

rectangle_t chernyshev::Rectangle::getFrameRect()const
{ 
  rectangle_t rect;
  rect.width = width_;
  rect.height = height_;
  rect.pos = center_;
  return rectangle_t{width_,height_,center_};;
}    

void chernyshev::Rectangle::Move(double delta_x,double delta_y)
{
  center_.x += delta_x;
  center_.y += delta_y;
}
 
void chernyshev::Rectangle::Move(point_t newPoint)
{
  center_.x = newPoint.x;
  center_.y = newPoint.y;
}

void chernyshev::Rectangle::scale(double size)
{
  if (size < 0.0)
  {
    throw std::invalid_argument("Koeff must be >=0");
  }
  height_ *= size;
  width_ *= size;
}

void chernyshev::Rectangle::printScale() const
{
  std::cout<<"Scale. Height is "<<height_<<std::endl;
  std::cout<<"Scale. Width is "<<width_<<std::endl;
}
