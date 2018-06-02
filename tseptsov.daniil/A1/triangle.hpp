#ifndef A1_TRIANGLE_HPP
#define A1_TRIANGLE_HPP

#include "shape.hpp"

class Triangle : public Shape {
public:
  Triangle(const point_t &A, const point_t &B, const point_t &C);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &pos) override;
  void move(const double Ox, const double Oy) override;
  void OutData() const override;
  point_t spotofcenter() const;

private:
  point_t A_, B_, C_;
  point_t center_;

};

#endif
