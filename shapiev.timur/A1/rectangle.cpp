#include "rectangle.hpp"
#include <iostream>
#include <assert.h>

Rectangle::Rectangle (const double Nwidth,const double Nheight,const point_t & center):
  rect_({Nwidth, Nheight, center})
{
  assert (Nwidth >= 0 && Nheight >= 0);
}

double Rectangle::getArea() const {
  return rect_.width * rect_.height;
}

rectangle_t Rectangle::getFrameRect() const {
  return rect_;
}

void Rectangle::move( const point_t & resPoint){
  rect_.pos = resPoint;
}

void Rectangle::move(const double dx,const double dy){
  rect_.pos.x+= dx;
  rect_.pos.y+= dy;
}
void Rectangle::printRect() const {
  std::cout << "Rectangle has width - " << rect_.width <<", height - " << rect_.height << std::endl;
  std::cout << "  Center is in (" << rect_.pos.x << ", " << rect_.pos.y << ')' << std::endl;
}
