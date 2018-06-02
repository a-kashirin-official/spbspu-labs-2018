#include "rectangle.hpp"
#include <cassert>
#include <iostream>
Rectangle::Rectangle(double w,double h,point_t c): height_(h),width_(w),center_(c)
{
  assert(h>=0.0);
  assert(w>=0.0);
}

double Rectangle::getArea()const
{
  return height_*width_;
}

rectangle_t Rectangle::getFrameRect()const
{ 
  rectangle_t rect;
  rect.width = width_;
  rect.height = height_;
  rect.pos = center_;
  return rectangle_t{width_,height_,center_};;
}    

void Rectangle::Move(double delta_x,double delta_y)
{
  center_.x += delta_x;
  center_.y += delta_y;
}
 
void Rectangle::Move(point_t newPoint)
{
  center_.x = newPoint.x;
  center_.y = newPoint.y;
}
