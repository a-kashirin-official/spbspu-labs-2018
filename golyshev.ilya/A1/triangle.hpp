#ifndef A1_TRIANGLE_HPP
#define A1_TRIANGLE_HPP

#include "shape.hpp"

class Triangle : public Shape
{
public:
  Triangle(const point_t &A, const point_t &B, const point_t &C);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &poss) override;
  void move(double Ox, double Oy) override;
  void OutInf() const override;

private:
  point_t A_;
  point_t B_;
  point_t C_;
  point_t center_;
};

#endif
