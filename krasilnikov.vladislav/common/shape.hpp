#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace krasilnikov
{
  class Shape
  {
    public:
      virtual ~Shape() = default;
      virtual double getArea() const = 0;
      virtual krasilnikov::rectangle_t getFrameRect() const = 0;
      virtual void move(const point_t & newPosition) = 0;
      virtual void move(const double dx, const double dy) = 0;
      virtual krasilnikov::point_t getPosition() const = 0;
      virtual void scale(const double factor) = 0;
      virtual void rotate(const double angle) = 0;
  };
}

#endif
