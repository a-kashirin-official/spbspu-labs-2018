#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle :
  public Shape {
public:
  Circle(double radius,const point_t &center);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(double dx, double dy) override;
  void move(const point_t & center) override;
  void print() const override;
private:
  double radius_;
  point_t center_;
};

#endif // CIRCLE_HPP
