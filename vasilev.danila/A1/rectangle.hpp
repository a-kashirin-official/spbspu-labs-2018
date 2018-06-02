#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"
class Rectangle :
    public Shape
{
public:
  Rectangle(double width, double height, const point_t &center_point);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const double dx, const double dy) override;
  void move(const point_t &point) override;
  void getInfo() const override;
private:
  double w_;
  double h_;
  point_t rectangle_center_;
};
#endif // RECTANGLE_HPP
