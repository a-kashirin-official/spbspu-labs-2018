#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace salykin
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const double dx, const double dy) = 0;
    virtual void move(const point_t & newPos) = 0;
    virtual point_t getPos() const = 0;
    virtual void scale(const double multiplier) = 0;
  };
}

#endif
