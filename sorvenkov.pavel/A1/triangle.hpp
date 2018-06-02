#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

class Triangle : public Shape
{
public:
  Triangle(const point_t& sd_a, const point_t& sd_b, const point_t& sd_c);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t& pos_n) override;
  void move(double dx, double dy) override;

private:
  point_t pos;
  point_t A_;
  point_t B_;
  point_t C_;
};

#endif
