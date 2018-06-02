#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

namespace iliintsev
{
  class Rectangle :
   public Shape
  {
  public:
    Rectangle(const point_t & center, double width, double height);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & new_center) override;
    void move(const double dx, const double dy) override;
    void scale(const double koef) override;
    point_t getCenter() const override;
  private:
    point_t center_;
    double width_;
    double height_;

  };
}

#endif
