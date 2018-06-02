#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

namespace kudryavtseva
{
  class Circle: public Shape
  {
  public:
    Circle(const point_t &circleCenter,const double r);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(const point_t &center) override;
    point_t getPos() const override;
    void printf() const override;
    void scale(double k) override;
    double getRadius() const;
    void rotate(double /*angle*/) override;
  private:
    point_t centerCircle_;
    double r_;
  };
}

#endif
