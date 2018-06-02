#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "shape.hpp"
#include "base-types.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const point_t &center, double width, double height);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(double dx, double dy) override;
  void move(const point_t &p) override;

private:
  rectangle_t rectangle_;
};

#endif
