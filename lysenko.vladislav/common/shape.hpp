#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace lysenko
{
  class Shape {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t &center) = 0;
    virtual void move(const double dx, const double dy) = 0;
    virtual void scale(const double dk) = 0;
  };
}
#endif
