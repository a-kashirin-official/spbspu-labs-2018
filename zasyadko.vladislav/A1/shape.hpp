#ifndef SHAPE_HEADER
#define SHAPE_HEADER

#include "base-types.hpp"

class Shape
{
  public:

  virtual ~Shape() = default;
  
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  
  virtual void move(const point_t & Center) = 0;
  virtual void move(const double add_x, const double add_y) = 0;
  
  virtual void print() const = 0;
};

#endif
  
