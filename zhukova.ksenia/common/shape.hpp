
#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace zhukova
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void move(const point_t & point) = 0;
    virtual void scale(double coefficient) = 0;
    virtual void rotate(double deg) = 0;
  };
}


#endif // SHAPE_HPP
