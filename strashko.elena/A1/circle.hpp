#ifndef HPP_CIRCLE
#define HPP_CIRCLE

#include "shape.hpp"

class Circle : 
  public Shape
{
public:
  Circle(const point_t &centre, double radius);

  double getArea() const override;
  rectangle_t getFrameRect() const override;

private:
  double radius_;
};

#endif
