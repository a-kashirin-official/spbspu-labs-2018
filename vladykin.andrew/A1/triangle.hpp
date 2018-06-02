#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

class Triangle : public Shape
{
public:
  Triangle(const point_t &a, const point_t &b, const point_t &c);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void showSize() const override;
  void showPos() const override;
  void move(const point_t &pos) override;
  void move(const double dx, const double dy) override;
private:
  point_t pos_;
  point_t A_;
  point_t B_;
  point_t C_;
};

#endif 
