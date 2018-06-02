#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "base-types.hpp"
#include "shape.hpp"

namespace chernyshev
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(double h,double w,point_t c);
    double getArea()const override;
    rectangle_t getFrameRect()const override;
    void Move(double delta_x,double delta_y) override;
    void Move(point_t newPoint) override;
    void scale(double size) override;
    void printScale()const override;
  private:
    double height_,width_;
    point_t center_;
  };
}
#endif
