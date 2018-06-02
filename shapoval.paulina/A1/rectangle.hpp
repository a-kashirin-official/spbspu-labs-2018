#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle:
  public Shape
{
public:
  Rectangle(const point_t & center, const double widht, const double height);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & new_centre) override;
  void move(const double dx, const double dy) override;
private:
  point_t centre_;
  double width_;
  double height_;
};

#endif
