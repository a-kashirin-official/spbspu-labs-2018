#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"
namespace gessen
{
  class Shape
  {
    public:
      virtual ~Shape() = default;
      virtual double getArea() const = 0;
      virtual rectangle_t getFrameRect() const = 0;
      virtual void move (const double dx, const double dy) = 0;
      virtual void move (const point_t & newPoint) = 0;
      virtual void scale (const double dk) = 0;
      virtual void rotate (const double angleRotate) = 0;
      virtual void printShapeName() const = 0;
  };
}
#endif

