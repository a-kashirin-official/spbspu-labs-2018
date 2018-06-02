#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace lobanova {
  class Shape {
  public:
    virtual ~Shape() = default;

    virtual double getArea() const = 0;

    virtual rectangle_t getFrameRect() const = 0;

    virtual void move(const point_t &a) = 0;

    virtual void move(double dx, double dy) = 0;

    virtual void scale(double p) = 0;

    virtual void rotate(double p) = 0;

    virtual void rotatePoint(const point_t &c, double p) = 0;

  };
}
#endif //SHAPE_HPP
