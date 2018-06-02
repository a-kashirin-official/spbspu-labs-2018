#include "circle.hpp"
#include <cassert>
#include <cmath>

Circle::Circle(double r,point_t c):
  rad_(r),
  center_(c)        
{
  assert ( r >= 0.0 );
}

double Circle::getArea()const
{
  return M_PI*rad_*rad_;
}

rectangle_t Circle::getFrameRect()const
{
  return rectangle_t{2*rad_,2*rad_,center_};
}

void Circle::Move(double delta_x,double delta_y)
{
  center_.x += delta_x;
  center_.y += delta_y;
}
void Circle::Move(point_t newPoint)
{
  center_ = newPoint;
}
