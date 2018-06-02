#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "base-types.hpp"
class Shape 
{
public:    
  virtual ~Shape() = default;
  virtual double getArea()const = 0;
  virtual rectangle_t getFrameRect()const = 0;
  virtual void Move(double xx,double yy) = 0;
  virtual void Move(point_t newPoint) = 0;
};
#endif
