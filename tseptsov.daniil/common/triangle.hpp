#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

namespace tseptsov
{

  class Triangle : public tseptsov::Shape
  {
  public:
    Triangle(const point_t &A, const point_t &B, const point_t &C);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &pos) override;
    void move(const double Ox, const double Oy) override;
    void OutData() const override;
    point_t getCenter() const override ;
    void scale(double coef) override;
    void rotate(double deg) override;
  private:
    point_t A_, B_, C_;
    point_t center_;
  };
}

#endif
