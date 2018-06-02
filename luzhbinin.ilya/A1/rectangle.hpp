#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const rectangle_t & rectan);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & to) override;
  void move(double dx, double dy) override;
private:
  rectangle_t rectan_;
};

#endif
