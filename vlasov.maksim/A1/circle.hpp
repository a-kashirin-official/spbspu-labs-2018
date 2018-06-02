#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

class Circle: public Shape {
public:
  Circle(double _radius, point_t _pos);

  virtual double getArea() const override;

  virtual rectangle_t getFrameRect() const override;
private:
  bool confirm = true;
  double radius;
};
#endif 
