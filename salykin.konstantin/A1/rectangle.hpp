#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle:
  public Shape
{
public:
  Rectangle(double width, double height, const point_t& center);
  virtual double getArea() const override;
  virtual rectangle_t getFrameRect() const override;
  virtual void move(const point_t& newPos);
  virtual void move(double dx, double dy);
private:
  point_t center_;
  double width_, height_;
};

#endif //RECTANGLE_HPP
