#ifndef A3_SHAPE_HPP
#define A3_SHAPE_HPP

#include "base-types.hpp"

namespace turkin
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t &pos) = 0;
    virtual void move(double Ox, double Oy) = 0;
    virtual void printInfo() = 0;
    virtual void scale(double k) = 0;
    virtual void rotate(double angle) = 0;
    virtual point_t getCenter() const = 0;
  };
}

#endif
