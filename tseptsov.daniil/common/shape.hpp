#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <memory>
#include "base-types.hpp"


namespace tseptsov
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t &pos) = 0;
    virtual void move(double Ox, double Oy) = 0;
    virtual void OutData() const = 0;
    virtual void scale(double coef) = 0;
    virtual void rotate(double deg) = 0;
    virtual point_t getCenter() const = 0;
  };
}

#endif

