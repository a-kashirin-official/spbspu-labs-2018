#ifndef A1_CIRCLE_HPP
#define A1_CIRCLE_HPP

#include "shape.hpp"

class Circle: public Shape
{
public:
  Circle(double r, point_t c);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(point_t c) override;
  void move(double dx, double dy) override;

private:
  double radius_;
  point_t center_;
};

#endif //A1_CIRCLE_HPP
