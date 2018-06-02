#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace pichugina
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual pichugina::rectangle_t getFrameRect() const = 0;
    virtual void move(const pichugina::point_t & pos) = 0;
    virtual void move(const double dx, const double dy) = 0;
    virtual void scale(const double factor) = 0;
  };
}

#endif
