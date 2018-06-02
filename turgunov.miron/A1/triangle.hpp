#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "shape.hpp"

class Triangle: public Shape
{
public:
  Triangle(const point_t &pos_a, const point_t &pos_b, const point_t &pos_c);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &point) override;
  void move(double dx, double dy) override;
  void printShapeInfo() const override;

private:
  point_t pos_;
  point_t pos_a_;
  point_t pos_b_;
  point_t pos_c_;
  double getMin(double first, double second, double third) const;
  double getMax(double first, double second, double third) const;
};

#endif
