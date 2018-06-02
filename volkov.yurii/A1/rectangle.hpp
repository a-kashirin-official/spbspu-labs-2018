#ifndef RECTANGLE_HPP
#define RECTSNGLE_HPP
#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const point_t &p, double w, double h);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &p) override;
  void move(double dx, double dy) override;

private:
  double width_;
  double height_;
  point_t point_;
};
#endif
