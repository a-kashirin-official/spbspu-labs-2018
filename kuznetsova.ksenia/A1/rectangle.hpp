#ifndef HPP_RECTANGLE
#define HPP_RECTANGLE
#include "shape.hpp"

class Rectangle :
  public Shape
{
public:
  Rectangle(point_t &centre, double width, double height);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(point_t &newcentre) override;
  void move(double dx, double dy) override;
private:
  point_t centre_;
  double width_;
  double height_;

};
#endif
