#ifndef RECTANGLE_HPP_G
#define RECTANGLE_HPP_G

#include "shape.hpp"

class Rectangle: public Shape
{
public:
  Rectangle(const point_t &pos, const double width, const double height);
  void move(const point_t &pos);
  void move(const double dx, const double dy);
  double getArea() const;
  rectangle_t getFrameRect() const;
  void printInfo() const;

private:
  point_t pos_;
  double width_;
  double height_;
};

#endif
