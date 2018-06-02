#ifndef A1_RECTANGLE_HPP
#define A1_RECTANGLE_HPP

#include "shape.hpp"

class Rectangle:
  public Shape {
public:
  Rectangle(const point_t & Center, double wdt, double hgh);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & newCenter) override;
  void move(double dx, double dy) override;
private:
  point_t pos;
  double width;
  double height;
};

#endif //A1_RECTANGLE_HPP
