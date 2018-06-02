#include "rectangle.hpp"
#include <stdexcept>

using namespace vertola;

Rectangle::Rectangle(const rectangle_t & r):
  rect_(r)
{
  if(rect_.width < 0.0){
    throw std::invalid_argument("ERR WIDTH");
  }
  if(rect_.height < 0.0){
    throw std::invalid_argument("ERR HEIGHT");
  }
}

double Rectangle::getArea() const
{
  return (rect_.width * rect_.height);
}

rectangle_t Rectangle::getFrameRect() const
{
  return rect_;
}

void Rectangle::move(const point_t & point) 
{
  rect_.pos = point;
}

void Rectangle::move(const double dx, const double dy) 
{
  rect_.pos.x += dx;
  rect_.pos.y += dy;
}

void Rectangle::scale(const double scf)
{
  if (scf < 0.0){
    throw std::invalid_argument("scale Value < 0.0");
  }
  rect_.width *= scf;
  rect_.height *= scf;
}
