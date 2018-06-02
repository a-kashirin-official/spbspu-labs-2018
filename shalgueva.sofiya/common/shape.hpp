#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace shalgueva
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void move(const point_t & posTo) = 0;
    virtual void scale(double coefficient) = 0;
    virtual void rotate(double alpha) = 0;
  };
} // shalgueva

#endif // SHAPE_HPP
