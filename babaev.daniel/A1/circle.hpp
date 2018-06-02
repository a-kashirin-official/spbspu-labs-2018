#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"
#include "base-types.hpp"

class Circle : public Shape
{
public:
  //  Radius, Cords of center (x, y)
  Circle(double r, double x, double y);

  double getArea() const override;

  rectangle_t getFrameRect() const override;

  void move(point_t c) override;

  void move(double dx, double dy) override;

  void printInfo() const override;

private:

  double rad_;

  point_t center_;

};

#endif
