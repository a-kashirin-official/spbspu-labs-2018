#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "base-types.hpp"
#include "shape.hpp"
class Rectangle : public Shape
{
public:
  Rectangle(double width,double height, const point_t& rec);
  double getArea() const;
  rectangle_t getFrameRect() const;
  void move(double dx,double dy);
  void move(const point_t& center);
private:
  double width_;
  double height_;
  point_t rec_;
};

#endif // RECTANGLE_H
