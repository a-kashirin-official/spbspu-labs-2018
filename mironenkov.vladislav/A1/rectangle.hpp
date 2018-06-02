#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle:public Shape
{
private:
  double width_;
  double height_;
public:
  Rectangle(const point_t & pos, const double width, const double height);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & pos) override;
  void move(const double dx, const double dy) override;
};

#endif //RECTANGLE_HPP
