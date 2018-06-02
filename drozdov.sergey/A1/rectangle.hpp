#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : 
  public Shape
{
public:
  Rectangle(const rectangle_t & rctng);
  double getArea() const noexcept override;
  rectangle_t getFrameRect() const noexcept override;
  void move(const point_t & point) noexcept override;
  void move(const double dx, const double dy) noexcept override;
private:
  rectangle_t rec;
};

#endif
