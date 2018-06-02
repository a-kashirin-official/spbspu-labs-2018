#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "base-types.hpp"
class Shape
{
public:
  Shape(const point_t & _pos);

  virtual double getArea() const = 0;

  virtual rectangle_t getFrameRect() const = 0;

  virtual void move(const point_t &arrival);

  virtual void move(double difX, double difY);

  virtual void showPosition() const;

  virtual ~Shape()=default;
  protected:
  point_t pos;
};
#endif
