#include "base-types.hpp"

#ifndef SHAPE_HPP
#define SHAPE_HPP

namespace aleksovski
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual point_t getCentre() const = 0;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void move(const point_t & p) = 0;
    virtual void scale(double k) = 0;
  };
}
#endif 
