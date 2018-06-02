#include "circle.hpp"
#include <iostream>
#include <math.h>

namespace kudryakov
{
  Circle::Circle(const point_t &center, const double radius) :
    center_(center),
    radius_(radius)
  {
    if (radius < 0.0)
    {
      throw std::invalid_argument("Radius can't be negative");
    }
  }
  
  double Circle::getArea() const
  {
    return M_PI * radius_ * radius_;
  }
  
  rectangle_t Circle::getFrameRect() const
  {
    return {center_, radius_ * 2, radius_ * 2};
  }
  
  void Circle::move(const point_t &newCenterPoint)
  {
    center_ = newCenterPoint;
  }
  
  void Circle::move(const double dx, const double dy)
  {
    center_.x += dx;
    center_.y += dy;
  }
  
  void Circle::scale(const double factor)
  {
    if (factor < 0.0)
    {
      throw std::invalid_argument("Factor can't be negative");
    }
    radius_ *= factor;
  }
}
