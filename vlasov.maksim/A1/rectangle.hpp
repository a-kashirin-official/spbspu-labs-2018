#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

class Rectangle: public Shape
{
public:
  Rectangle(double _width, double _height, point_t  _pos);

  virtual double getArea() const override;

  virtual rectangle_t getFrameRect() const override;
private:
  double width;
  double height;
  bool confirm=true;
};
#endif
