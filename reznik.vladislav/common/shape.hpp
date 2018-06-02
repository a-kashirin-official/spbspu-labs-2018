#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>
#include "base-types.hpp"

namespace reznik
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual void scale(double k) = 0;
    virtual double getArea() const = 0;
    virtual reznik::rectangle_t getFrameRect() const = 0;
    virtual void move(double dx,double dy) = 0;
    virtual void move(const point_t& center) = 0;
  };
}
#endif // SHAPE_H 
