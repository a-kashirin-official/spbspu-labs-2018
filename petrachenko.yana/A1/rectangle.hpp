#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

class Rectangle:public Shape
{
public:
  Rectangle(const double width, const double height, const point_t &center);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &p) override;
  void move(const double dx, const double dy) override;
private:
  double width_, height_;
  point_t center_;
};

#endif

