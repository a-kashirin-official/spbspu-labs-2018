#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include "base-types.hpp"

class Shape
{
public:
  virtual ~Shape() = default;
  friend std::ostream & operator<<(std::ostream & out, const Shape & shape);
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(const point_t & point) = 0;
  virtual void move(const double dx, const double dy) = 0;
private:
  virtual void print(std::ostream & out) const = 0;
};

#endif
