#ifndef MAIN_SHAPE_HPP_FILE
#define MAIN_SHAPE_HPP_FILE

#include "base-types.hpp"

class Shape
{
public:
  virtual ~Shape() = default;

  virtual void move(const point_t &newP) = 0;
  virtual void move(const double &nX, const double &nY) = 0;

  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
};

#endif
