#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

class Rectangle : public Shape {
public:
  Rectangle(double height, double width, double x, double y);
  
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(point_t c) override;
  void move(double dx, double dy) override;
  
  void writeInfoOfObject() const override;
  
private:
  double height_, width_;
  point_t center_;
};
#endif