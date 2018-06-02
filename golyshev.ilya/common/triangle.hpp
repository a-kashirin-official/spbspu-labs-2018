#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

namespace golyshev
{
  class Triangle : public golyshev::Shape
  {
  public:
    Triangle(const point_t &A, const point_t &B, const point_t &C);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &poss) override;
    void move(double Ox, double Oy) override;
    void scale(double coeff) override;
    void rotate(const double angle) override;
    void OutInf() const override;


  private:
    point_t A_;
    point_t B_;
    point_t C_;
    point_t center_;
  };
}

#endif
