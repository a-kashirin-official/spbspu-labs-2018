#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const rectangle_t & set_coordinate_size);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & new_center) override;
  void move(const double dx, const double dy) override;
private:
  rectangle_t coordinate_size_;
};

#endif
