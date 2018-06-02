#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace kramarov
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual rectangle_t getFrameRect() const = 0;
    virtual double getArea() const = 0;
    virtual void move (const double dx, const double dy) = 0;
    virtual void move (const point_t & newLocation) = 0;
    virtual void scale (const double scaleRate) = 0;
    virtual point_t getXY() const = 0;
  };
}

#endif
