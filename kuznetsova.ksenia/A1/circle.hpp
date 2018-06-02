#ifndef HPP_CIRCLE
#define HPP_CIRCLE
#include "shape.hpp"

class Circle :
  public Shape
{
public:
  Circle(point_t &centre, double radius);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(point_t &newcentre) override;
  void move(double dx, double dy) override;
private:
  point_t centre_;
  double radius_;
};
#endif
