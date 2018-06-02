#ifndef CIRCLE_H
#define CIRCLE_H
#include "shape.hpp"


class Circle : public Shape
{
public:
  Circle(const point_t & center, double radius);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(double dx, double dy) override;
  void move(const point_t & p) override;

private:
  point_t centar_;
  double radius_;
};

#endif
