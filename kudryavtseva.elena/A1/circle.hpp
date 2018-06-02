#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

class Circle: public Shape
{
public:
  Circle(const point_t & circleCenter,const double r);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(double dx, double dy) override;
  void move(const point_t &center) override;
  void printf() override;
  point_t getPos();
private:
  point_t centerCircle_;
  double r_;
};

#endif
