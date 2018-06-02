#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace zabrodina
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual zabrodina::rectangle_t getFrameRect() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void move(const zabrodina::point_t &p) = 0;
    virtual void printInf() const = 0;
    virtual void scale(const double coefficient) = 0;
  };
}

#endif 
