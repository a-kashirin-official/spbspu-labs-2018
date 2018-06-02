#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const point_t & center, double height, double width);
  void move(const point_t & pos) override;
  void move(double dx, double dy) override;
  double getArea() const override;
  rectangle_t getFrameRect() const override;

private:
  rectangle_t rect_;
};

#endif // RECTANGLE_HPP
