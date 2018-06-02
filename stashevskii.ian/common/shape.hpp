#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "base-types.hpp"

namespace stashevskii
{
  class Shape
  {
  public:
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const double dx, const double dy) = 0;
    virtual void move(const point_t &point) = 0;
    virtual void scale(const double k) = 0;
    virtual ~Shape() = default;
    virtual point_t getPosition() const = 0;
    virtual void rotate(const double angle) =0;
  };
}

#endif
