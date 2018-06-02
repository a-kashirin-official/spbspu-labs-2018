#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"
class Circle:
  public Shape
{
public:
  Circle(double radius, const point_t &center_point);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const double dx, const double dy) override;
  void move(const point_t &circ_point) override;
  void getInfo() const override;
private:
  double r_;
  point_t circle_center_;
};
#endif // CIRCLE_HPP
