#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace korichev
{
  class Shape
  {
  public:
    // Destructor
    virtual ~Shape() = default;
    // Get Area Method
    virtual double getArea() const = 0;
    // Get Frame Method
    virtual rectangle_t getFrameRect() const = 0;
    // Move by dx and dy method
    virtual void move(double dx, double dy) = 0;
    // Move to the point method
    virtual void move(const point_t & pos) = 0;
    // Scale
    virtual void scale(double ratio) = 0;
    // Rotate
    virtual void rotate(double angle) = 0;
  };
}

#endif
