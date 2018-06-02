#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"


class Rectangle : public Shape
{
public:
  Rectangle(const point_t & center, double height, double width);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(double dx, double dy) override;
  void move(const point_t & p) override;

private:
  rectangle_t rect_;
};
#endif
