#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle:
  public Shape
{
public:
  Rectangle(const double width, const double height, const point_t & mid);
  double getArea() const noexcept override;
  rectangle_t getFrameRect() const noexcept override;
  void move(const point_t & newPos) noexcept override;
  void move(const double dx, const double dy) noexcept override;
private:
  point_t mid_;
  double width_;
  double height_;
};

#endif
