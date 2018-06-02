#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace ryabov {
  class Shape {
    public:
      virtual ~Shape() = default;
      virtual double getArea() const = 0;
      virtual rectangle_t getFrameRect() const = 0;
      virtual point_t move(const point_t &coords) = 0;
      virtual point_t move(double dx, double dy) = 0;
      virtual void scale(double factor) = 0;
  };
}

#endif
