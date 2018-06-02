#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace hvetsckovich
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual point_t getPos() const = 0;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t & pos) = 0;
    virtual void move(const double dx, const double dy) = 0;
    virtual void scale(const double factor) = 0;
    virtual void rotate(const double degrees) = 0;
  };
}

#endif
