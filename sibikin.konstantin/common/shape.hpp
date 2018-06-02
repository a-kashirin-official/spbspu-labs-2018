#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace sibikin
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual point_t getPos() const = 0;
    virtual void move(const point_t & newCenter) = 0;
    virtual void move(const double dx, const double dy) = 0;
    virtual void scale(const double coef) = 0;
    virtual void rotate(const double phi) = 0;
  };
}

#endif