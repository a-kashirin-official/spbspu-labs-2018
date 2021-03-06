#ifndef WORK_SHAPE_HPP
#define WORK_SHAPE_HPP

#include "base-types.hpp"

namespace ivanov
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t & newCentrePoint) = 0;
    virtual void move(const double dx, const double dy) = 0;
    virtual void scale(const double ratio) = 0;
  };
}

#endif
