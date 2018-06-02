//  This file contains definition of abstract class Shape
#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "base-types.hpp"

namespace neizhko
{
  class Shape
  {
    public:

      virtual ~Shape() = default;

      virtual double getArea() const = 0;

      virtual rectangle_t getFrameRect() const = 0;
      // Replace by x,y
      virtual void move(double dx, double dy) = 0;
      // Move to point
      virtual void move(point_t c) = 0;
      // Print information about figure
      virtual void printInfo() const = 0;
  
      virtual void scale(double ratio) = 0;

  };
}

#endif
