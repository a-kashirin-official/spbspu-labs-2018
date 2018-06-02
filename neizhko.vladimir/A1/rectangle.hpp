#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"
#include "base-types.hpp"

class Rectangle : public Shape
{
public:
  //  Height, width, cords (x, y) of center of figure
  Rectangle(double h, double w, double x, double y);

  double getArea() const override;

  rectangle_t getFrameRect() const override;

  void move(point_t c) override;

  void move(double dx, double dy) override;

  void printInfo() const override;

private:

  point_t center_;

  double height_;

  double width_;

};

#endif
