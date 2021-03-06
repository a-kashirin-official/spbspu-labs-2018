#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "base-types.hpp"

namespace koryakin
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const double dx, const double dy) = 0;
    virtual void move(const point_t &p) = 0;
    virtual void scale(const double factor) = 0;
  };
} //koryakin 13534/6

#endif
