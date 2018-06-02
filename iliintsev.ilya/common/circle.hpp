#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

namespace iliintsev
{
  class Circle : 
    public Shape
  {
  public:
    Circle(const point_t & set_coord, double set_r);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & new_center) override;
    void move(const double dx, const double dy) override;
    void scale(const double koef) override;
    point_t getCenter() const override;    
  private:
    point_t center_;
    double r_;
  };
}

#endif
