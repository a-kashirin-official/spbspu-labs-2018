#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "base-types.hpp"

namespace chernyshev
{
  class Shape 
  {
  public:    
    virtual ~Shape() = default;
    virtual double getArea()const = 0;
    virtual rectangle_t getFrameRect()const = 0;
    virtual void Move(double delta_x,double delta_y) = 0;
    virtual void Move(point_t newPoint) = 0;
    virtual void scale(double size) = 0; 
    virtual void printScale() const =0;
  };
}
#endif
