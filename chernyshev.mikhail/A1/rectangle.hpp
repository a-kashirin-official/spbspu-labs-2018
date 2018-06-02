#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"
#include "base-types.hpp"
class Rectangle : public Shape
{
public:
  Rectangle(double h,double w,point_t c);
  double getArea()const override;
  rectangle_t getFrameRect()const override;
  void Move(double xx,double yy) override;
  void Move(point_t newPoint) override;
private:
  double height_,width_;
  point_t center_;
};
#endif
