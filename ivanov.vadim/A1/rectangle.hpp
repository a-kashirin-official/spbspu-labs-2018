#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle: public Shape
{
public:
  Rectangle(const point_t & centr, double height, double width);
  rectangle_t getFrameRect() const override;
  double getArea() const override;
  void move(const point_t & posit) override;
  void move(double dx, double dy) override;

private:
  rectangle_t rec_;
};
#endif // RECTANGLE_HPP
