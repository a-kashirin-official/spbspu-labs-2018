#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle : 
  public Shape
{
public:
  Circle(const double radius, const point_t & point);
  double getArea() const noexcept override;
  rectangle_t getFrameRect() const noexcept override;
  void move(const point_t & point) noexcept override;
  void move(const double dx, const double dy) noexcept override;
private:
  point_t cpoint;
  double r;
};

#endif
