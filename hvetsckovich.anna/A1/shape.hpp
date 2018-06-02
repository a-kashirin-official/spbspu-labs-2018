#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

class Shape
{
public:
  virtual ~Shape() = default;//distructor
  virtual double getArea() const = 0;//pure
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(const point_t & pos) = 0;
  virtual void move(const double dx, const double dy) = 0;
};

#endif
