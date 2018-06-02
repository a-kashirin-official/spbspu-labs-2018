#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "base-types.hpp"

namespace ivanov
{
class Shape
{
public:
  virtual ~Shape() = default;
  virtual void show() const = 0;
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(const point_t & p) = 0;
  virtual void move(double dx, double dy) = 0;
  virtual void scale(double koeff) = 0;
};
}
#endif // SHAPE_HPP
