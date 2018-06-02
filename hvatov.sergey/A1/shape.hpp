#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>

#include "base-types.hpp"

// shape abstract class
class Shape
{
  // Public members
public:
  // Virtual destructor of the class
  virtual ~Shape() = default;

  // Get area method
  virtual double getArea() const = 0;

  // Get frame rectangle method
  virtual rectangle_t getFrameRect() const = 0;

  // Move to the point method
  virtual void move(const point_t & pos) = 0;

  // Move by dx and dy
  virtual void move(double dx, double dy) = 0;
};

#endif // SHAPE_HPP

