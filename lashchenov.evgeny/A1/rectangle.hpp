#ifndef A1_RECTANGLE_HPP
#define A1_RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(double width, double height, point_t center);
  Rectangle(double width, double height, double x, double y);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & center) override;
  void move(double dx, double dy) override;
  void printInfo() const override;

private:
  double width_;
  double height_;
  point_t center_;
};

#endif //A1_RECTANGLE_HPP
