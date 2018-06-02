#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace sergeev
{
  class Shape
  {
    public:
      virtual ~Shape() = default;
      virtual double getArea() const = 0;
      virtual rectangle_t getFrameRect() const = 0;
      virtual void move(const point_t & point) = 0;
      virtual void move(double dx, double dy) = 0;
      virtual void scale(double factor) = 0;
      virtual void rotate(double angle) = 0;
  };
}

#endif // SHAPE_HPP
