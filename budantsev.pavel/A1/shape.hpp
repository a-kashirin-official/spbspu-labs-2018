#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

class Shape
{
public:
  virtual ~Shape() = default;
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(const point_t& poss) = 0;
  virtual void move(const double Ox, const double Oy) = 0;
  virtual void info() const = 0;

};

#endif //AA2_SHAPE_HPP
