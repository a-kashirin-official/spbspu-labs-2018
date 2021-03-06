#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle: 
  public Shape
{
public:
  Circle(const point_t & centre, const double radius);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & new_centre) override;
  void move(const double dx, const double dy) override;
private:
  point_t centre_;
  double radius_;
};

#endif
