#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace golyshev
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t &poss) = 0;
    virtual void move(double Ox, double Oy) = 0;
    virtual void scale(double coeff) = 0;
    virtual void rotate(const double angle) = 0;
    virtual void OutInf() const = 0;
  };
}

#endif
