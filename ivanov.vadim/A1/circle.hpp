#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle (const point_t & posit, double radius);
  rectangle_t getFrameRect() const override;
  double getArea() const override;
  void move(const point_t & posit) override;
  void move(double dx, double dy) override;

private:
  point_t centr_;
  double rad_;
};

#endif // CIRCLE_HPP
