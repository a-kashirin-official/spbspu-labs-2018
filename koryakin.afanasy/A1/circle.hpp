#ifndef CIRCLE_H
#define CIRCLE_H
#include "shape.hpp"
#include "base-types.hpp"

class Circle : public Shape
{
public:
  Circle(const point_t &center, const double radius);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const double dx, const double dy) override;
  void move(const point_t &p) override;

private:
  point_t center_;
  double radius_;
};

#endif
