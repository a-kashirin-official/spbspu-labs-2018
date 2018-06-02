#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace golyshev
{
  class Circle : public golyshev::Shape
  {
  public:
    Circle(double rad, const point_t &poss);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &poss) override;
    void move(double Ox, double Oy) override;
    void scale(double coeff) override;
    void rotate(const double /*angle*/) override;
    void OutInf() const override;

  private:
    double radius_;
    point_t center_;
  };
}
#endif
