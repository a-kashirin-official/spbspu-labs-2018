#ifndef A1_CIRCLE_HPP
#define A1_CIRCLE_HPP

#include "shape.hpp"

class Circle:
  public Shape {
public:
  Circle(const point_t & center, double rad);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & newCenter) override;
  void move(double dx, double dy) override;

private:
  point_t pos;
  double radius;
};

#endif //A1_CIRCLE_HPP
