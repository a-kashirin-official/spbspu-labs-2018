#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.hpp"

class Rectangle :
  public Shape {
public:
  Rectangle(double width, double height,const point_t& rect);
  double getWidth() const;
  double getHeight() const;
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(double dx, double dy) override;
  void move(const point_t & center) override;
  void print() const override;
private :
  double w_;
  double h_;
  point_t center_;
};
#endif // RECTANGLE_HPP
