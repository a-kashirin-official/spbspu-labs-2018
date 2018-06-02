#ifndef HPP_SHAPE
#define HPP_SHAPE

#include "base-types.hpp"

class Shape {
public:
  virtual ~Shape() = default;

  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;

  virtual void move(double dx, double dy);
  virtual void move(const point_t &newcentre);

protected:
  point_t centre_;
};

#endif
