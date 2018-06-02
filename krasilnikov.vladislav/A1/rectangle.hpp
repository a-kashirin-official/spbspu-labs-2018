#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle:
  public Shape
{
public:
  Rectangle (const double height, const double width, const point_t & middle);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & newPosition) override;
  void move(const double dx, const double dy) override;

private:
  point_t middle_;
  double height_;
  double width_;
};

#endif
